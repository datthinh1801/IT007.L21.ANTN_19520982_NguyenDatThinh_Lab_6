# [IT007.L21.ANTN] Lab 6
> 19520982  
> Nguyen Dat Thinh  

## Bài tập ôn tập
### Câu 1
#### Nghịch lý Belady là gì?  
- Nghịch lý Belady là hiện tượng khi số lượng frames tăng lên thì số lượng lỗi trang có thể tăng lên. FIFO là thuật toán dễ bị ảnh hưởng nhất.  

#### Minh họa
Với các yêu cầu trang như sau:  
| 3 | 2 | 1 | 0 | 3 | 2 | 4 | 3 | 2 | 1 | 0 | 4 |
|---|---|---|---|---|---|---|---|---|---|---|---|  

Nghịch lý Belady sẽ xảy ra khi sử dụng thuật toán FIFO.  

#### Số frames bằng 3  
![image](https://user-images.githubusercontent.com/44528004/124384369-0bee4a00-dcfb-11eb-8fd2-fb8f659cc75a.png)  


| Trang | 3 | 2 | 1 | 0 | 3 | 2 | 4 | 3 | 2 | 1 | 0 | 4 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Frame 1 | 3 | 3 | 3 | 0 | 0 | 0 | 4 | 4 | 4 | 4 | 4 | 4 |
| Frame 2 |   | 2 | 2 | 2 | 3 | 3 | 3 | 3 | 3 | 1 | 1 | 1 |
| Frame 3 |   |   | 1 | 1 | 1 | 2 | 2 | 2 | 2 | 2 | 0 | 0 |
| Lỗi trang | * | * | * | * | * | * | * |  |  | * | * |   |  
> Số lượng lỗi trang là **9**.  

#### Số frames bằng 4
![image](https://user-images.githubusercontent.com/44528004/124384392-27f1eb80-dcfb-11eb-8079-b79022d5cca3.png)  


| Trang | 3 | 2 | 1 | 0 | 3 | 2 | 4 | 3 | 2 | 1 | 0 | 4 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Frame 1 | 3 | 3 | 3 | 3 | 3 | 3 | 4 | 4 | 4 | 4 | 0 | 0 |
| Frame 2 |  | 2 | 2 | 2 | 2 | 2 | 2 | 3 | 3 | 3 | 3 | 4 |
| Frame 3 |  |   | 1 | 1 | 1 | 1 | 1 | 1 | 2 | 2 | 2 | 2 |
| Frame 4 |  |   |   | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 |
| Lỗi trang | * | * | * | * |  |  | * | * | * | * | * | * |  
> Số lượng lỗi trang là **10**.  

### Bài 2
#### Giải thuật nào là bất khả thi nhất?
- Giải thuật OPT.  
- Vì đối với các chương trình phức tạp, hệ điều hành không thể nào biết trước được flow của tiến trình trong tương lai nên việc thực thi OPT là không thể.  

#### Giải thuật nào là phức tạp nhất?
- Giải thuật OPT. 
- Vì đối với giải thuật FIFO và LRU, hệ điều hành chỉ cần lưu lại trạng thái truy xuất của các trang ở trong frame và chỉ cần tính thời gian vào frame sớm nhất (FIFO) hoặc được truy xuất sớm nhất (LRU) là đã có thể hiện thực được 2 giải thuật này. Tuy nhiên đối với OPT, hệ điều hành phải biết trước được flow của tiến trình trong tương lai, đồng thời hệ điều hành phải thực hiện nhiều tác vụ kiểm tra hơn (kiểm tra xem trang nào không được thực thi trong tương lại, hoặc trang nào được thực thi trễ nhất trong tương lai).
