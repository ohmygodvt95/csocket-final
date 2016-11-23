# Ứng dụng chia sẻ file

### Server

* Tiến trình 1: 
** Đăng nhập, đăng ky user
*** Các giao thức

Đăng ký: 101,username,pass
Đăng nhập: 102,username,pass

***Các hàm chính

**** int login(char username[], char pass[]); trả về 200 nếu qua, 404 nếu không đc
**** int signin(char username[], char pass[]); trả về 200 nếu tạo đc user, 403 nếu user bị trùng
* Tiến trình 2: 

** Nhận request yêu cầu tìm kiếm file
*** Giao thức
Nhận: 201,keyword

** Gửi lại cho các client khác y/c tìm kiếm
*** Giao thức 
gửi: 202,keyword
**** int searchRequest(int sock[], char keyword[]); trả về  số client gửi thành công trên tổng số client đang kết nối
** Nhận các kết quả từ các client
***Giao thức:
Nhận:203,username,0||1,link
Hàm: int searchResponse(int sock); trả về 0 nếu thằng sock ko có file, trả về 1 nếu sock có file
** Gửi trả lại user có y/c tìm kiếm kết quả vừa rồi
Giao thức: 204,username|link,username1|link1...
hàm: int sendSearchResult(int sock, char result[]); trả về lựu chọn của user, 0 nếu ko chọn gì.

* Tiến trình 3:
** Client gửi lựa chọn file từ client khác
Nhận: 301,username,link
gửi: 302,user,link
** Nhận nội dung file từ thăng A tra ve cho B
*** Giao thức: 
Nhan: 303,username[15],FileName[15],byte[1000] username của ng NHẬN 
gUI: 304:username[15],FileName[15],byte[1000] username của ng gửi 
### Clientink

* Tiến trình 1:

** Đăng kys, đăng nhập
*** Các giao thức

Đăng ký: 101,username,pass
Đăng nhập: 102,username,pass

** Gửi lệnh tìm kiếm 
*** Giao thức: 201,keyword


** Nhận kết quả tìm kiếm

*** Giao thức:
Nhận: 204,username|link,username1|link1...
** Chọn trong kết quả trả về file muốn lấy
*** Giao thức: 

Gửi: 301,username,link

** Tiến hành lấy file

*** Giao thức: 
Nhận: 303,username[15],FileName[15],byte
* Tiến trình 2:

** Nhận lệnh tìm kiếm, trả về tên file nếu tìm thấy
*** Giao thức
Nhận: 202,keyword
Gửi :203,username,0||1,link
* Tiến trình 3:

** Gửi file lên server 
*** Giao thức 
Gửi: 304,username[15],FileName[15],byte[1000] (username của ng NHẬN )



