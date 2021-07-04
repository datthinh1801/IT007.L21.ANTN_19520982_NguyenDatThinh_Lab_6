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
