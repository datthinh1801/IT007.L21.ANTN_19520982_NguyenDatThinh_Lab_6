/*#######################################
# University of Information Technology  #
# IT007 Operating System                #
# Nguyen Dat Thinh                      #
# 19520982                              #
# File: main.cpp                        #
########################################*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void PrintSequence(const vector<int> &pages)
{
    for (int i = 0; i < pages.size(); ++i)
    {
        cout << pages[i] << ' ';
    }
    cout << endl;
}

void Stat(const vector<int> &pages, int num_frames, const vector<vector<int>> &result, int page_faults, const vector<int> &failures)
{
    cout << "Number of frames: " << num_frames << endl;
    cout << "Number of page faults: " << page_faults << endl;

    for (int i = 0; i < pages.size(); ++i)
    {
        cout << pages[i] << ' ';
    }
    cout << "\t<--- Page" << endl;

    for (int i = 0; i < num_frames; ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (i < result[j].size())
            {
                cout << result[j][i] << ' ';
            }
            else
            {
                cout << "  ";
            }
        }
        cout << "\t<--- Frame " << i << endl;
    }

    // Print delimiter for readability
    for (int i = 0; i < failures.size(); ++i)
    {
        cout << "--";
    }
    cout << endl;

    for (int i = 0; i < failures.size(); ++i)
    {
        cout << failures[i] << ' ';
    }
    cout << "\t<--- Page fault? (1 == true|0 == false)" << endl;
}

int FindPage(const vector<int> &sequence, int element)
{
    for (int i = 0; i < sequence.size(); ++i)
    {
        if (sequence[i] == element)
        {
            return i;
        }
    }
    return -1;
}

void FIFO(const vector<int> &pages, unsigned int num_frames)
{
    vector<vector<int>> results;
    queue<int> fifo_queue;
    vector<int> frames;
    vector<int> failures;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); ++i)
    {
        // If there are available frames
        if (frames.size() < num_frames)
        {
            // Find the current page in the frames
            int found_index = FindPage(frames, pages[i]);
            // If the current page is not in the frames
            if (found_index < 0)
            {
                // Insert the current page into the frames
                frames.push_back(pages[i]);
                // Add that page to the queue
                fifo_queue.push(pages[i]);
                // Increase page_faults
                ++page_faults;
                failures.push_back(1);
            }
            // If the current is already in the frames
            else
            {
                // do nothing
                failures.push_back(0);
            }
        }
        // If all frames are occupied
        else
        {
            // Find the current page in the frames
            int found_index = FindPage(frames, pages[i]);
            // If the current page is not in the frames
            if (found_index < 0)
            {
                // Pop the first page on the queue out
                int page_to_remove = fifo_queue.front();
                fifo_queue.pop();
                // Replace the page_to_remove with the current page
                int remove_index = FindPage(frames, page_to_remove);
                frames[remove_index] = pages[i];
                // Add the current page to the queue
                fifo_queue.push(pages[i]);
                // Increase page_faults
                ++page_faults;
                failures.push_back(1);
            }
            // If the current page is in the frames
            else
            {
                // do nothing
                failures.push_back(0);
            }
        }
        // Push the whole frames to results for later illustration
        results.push_back(frames);
    }

    // Report the result
    Stat(pages, num_frames, results, page_faults, failures);
}

void LRU(const vector<int> &pages, int num_frames)
{
    vector<vector<int>> results;
    queue<int> lru_queue;
    vector<int> frames;
    vector<int> failures;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); ++i)
    {
        // If there are available frames
        if (frames.size() < num_frames)
        {
            // Find the current page in the frames
            int found_index = FindPage(frames, pages[i]);
            // If not exist
            if (found_index < 0)
            {
                // Insert the current page into the frames
                frames.push_back(pages[i]);
                // Push the current page into the lru_queue
                lru_queue.push(pages[i]);
                // Increase page_faults
                ++page_faults;
                failures.push_back(1);
            }
            // If exist
            else
            {
                // Update the lru_queue
                queue<int> carrier = lru_queue;
                // Clear the lru_queue
                lru_queue = queue<int>();
                // Reconstruct the lru_queue
                // such that the current page is moved to the tail of the queue
                while (carrier.size() > 0)
                {
                    int next = carrier.front();
                    carrier.pop();

                    if (next != pages[i])
                    {
                        lru_queue.push(next);
                    }
                }
                lru_queue.push(pages[i]);
                failures.push_back(0);
            }
        }
        // If no available frames
        else
        {
            // Find the current page in the frames
            int found_index = FindPage(frames, pages[i]);
            // If not exist
            if (found_index < 0)
            {
                // Get the least recently used page
                int lru_page = lru_queue.front();
                lru_queue.pop();
                // Get the index of the lru page
                int remove_index = FindPage(frames, lru_page);
                // Replace the lru_page with the current page
                frames[remove_index] = pages[i];
                // Push the current page into the lru_queue
                lru_queue.push(pages[i]);
                // Increase page_faults
                ++page_faults;
                failures.push_back(1);
            }
            // If exist
            else
            {
                // Update the lru_queue
                queue<int> carrier = lru_queue;
                // Clear the lru_queue
                lru_queue = queue<int>();
                // Reconstruct the lru_queue
                // such that the current page is moved to the tail of the queue
                while (carrier.size() > 0)
                {
                    int next = carrier.front();
                    carrier.pop();

                    if (next != pages[i])
                    {
                        lru_queue.push(next);
                    }
                }
                lru_queue.push(pages[i]);
                failures.push_back(0);
            }
        }
        results.push_back(frames);
    }
    Stat(pages, num_frames, results, page_faults, failures);
}

int FindPageIndexToRemove(const vector<int> &pages, const vector<int> &frames, int current_page_idx)
{
    int total_furthest = current_page_idx;
    int furthest_idx = 0;

    // Loop through each frame
    for (int i = 0; i < frames.size(); ++i)
    {
        // Find the furthest occurence of the current frame
        int furthest = -1;
        for (int j = current_page_idx + 1; j < pages.size(); ++j)
        {
            if (pages[j] == frames[i])
            {
                furthest = j;
            }
        }

        // If the current frame is not reference in the future,
        // then return the index of the current frame
        if (furthest == -1)
        {
            return i;
        }
        // Otherwise
        else
        {
            // Update the total_furthest if necessary
            if (furthest > total_furthest)
            {
                total_furthest = furthest;
                furthest_idx = i;
            }
        }
    }

    return furthest_idx;
}

void OPT(const vector<int> &pages, int num_frames)
{
    vector<vector<int>> results;
    vector<int> frames;
    vector<int> occurences;
    vector<int> failures;
    int page_faults = 0;

    for (int i = 0; i < pages.size(); ++i)
    {
        // If there are available frames
        if (frames.size() < num_frames)
        {
            // Find the current page in the frames
            int found_index = FindPage(frames, pages[i]);
            // If not exist
            if (found_index < 0)
            {
                // Insert the current page into the frames
                frames.push_back(pages[i]);
                // Increase page_faults
                ++page_faults;
                failures.push_back(1);
            }
            // If exist
            else
            {
                // do nothing
                failures.push_back(0);
            }
        }
        // If no available frames
        else
        {
            // Find the current page in the frames
            int found_index = FindPage(frames, pages[i]);
            // If not exist
            if (found_index < 0)
            {
                // Find the index of the frame to replace
                int remove_index = FindPageIndexToRemove(pages, frames, i);
                // Replace that frame with the current page
                frames[remove_index] = pages[i];
                // Increase page_faults
                ++page_faults;
                failures.push_back(1);
            }
            // If exist
            else
            {
                // do nothing
                failures.push_back(0);
            }
        }
        results.push_back(frames);
    }
    Stat(pages, num_frames, results, page_faults, failures);
}

int main()
{
    vector<int> pages;
    int option;

    // Select the source of sequence
    cout << "Select the source of sequence:" << endl;
    cout << "(1) Default" << endl;
    cout << "(2) From console" << endl;
    cout << "> ";
    cin >> option;

    if (option == 1)
    {
        pages.push_back(1);
        pages.push_back(9);
        pages.push_back(5);
        pages.push_back(2);
        pages.push_back(0);
        pages.push_back(9);
        pages.push_back(8);
        pages.push_back(2);
        pages.push_back(0);
        pages.push_back(7);
    }
    else if (option == 2)
    {
        int num_pages;
        cout << "Number of pages: ";
        cin >> num_pages;

        int page;

        for (int i = 0; i < num_pages; ++i)
        {
            cout << "Page: ";
            cin >> page;
            pages.push_back(page);
        }
    }
    else
    {
        cout << "Invalid option!" << endl;
        exit(1);
    }

    // Get number of frames
    cout << "Number of frames: ";
    int num_frames;
    cin >> num_frames;

    // Select page replacement algorithm
    cout << "Select page replacement algorithm:" << endl;
    cout << "(1) FIFO" << endl;
    cout << "(2) OPT" << endl;
    cout << "(3) LRU" << endl;
    cout << "> ";
    cin >> option;

    switch (option)
    {
    case 1:
        FIFO(pages, num_frames);
        break;
    case 2:
        OPT(pages, num_frames);
        break;
    case 3:
        LRU(pages, num_frames);
        break;
    default:
        cout << "Invalid option!" << endl;
        exit(1);
    }

    return 0;
}
