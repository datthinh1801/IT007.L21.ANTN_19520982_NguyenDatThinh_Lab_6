# [IT007.L21.ANTN] Lab 6
> 19520982  
> Nguyen Dat Thinh  

## Bài tập ôn tập
### Câu 1
#### Nghịch lý Belady là gì?  
- Nghịch lý belady là hiện tượng khi số lượng frames tăng lên thì số lượng lỗi trang sẽ giảm đi hoặc không đổi.  

#### Minh họa
> Các ví dụ minh họa sau sử dụng input là `1, 9, 5, 2, 0, 9, 8, 2, 0, 7`.  

| Giải thuật | Số lượng frames | Số lỗi trang |
|---|---|---|
| FIFO | 3 | 10 |
| | 4 | 7 |
| | 5 | 7 |
| LRU | 3 | 10 |
| | 4 | 7 |
| | 5 | 7 |
| OPT | 3 | 7 |
| | 4 | 7 |
| | 5 | 7 |

