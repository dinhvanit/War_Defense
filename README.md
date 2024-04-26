# War_Defense
## Giới thiệu bản thân
- Họ và tên: Nguyễn Đình Văn
- Lớp: K68-J
- Mã sinh viên: 23020714
- Bài tập lớn INT2215_52 Lập trình nâng cao

## Giới thiệu game
- `War Defense` là một game thể loại thủ thành chiến thuật.Cố gắng bảo vệ ngôi nhà khi bị các quái vật xâm nhập bằng cách đặt hợp lý các loại tháp để tạo đường đi và có các chức năng khác nhau để tiêu diệt kẻ địch. Kẻ địch là các loại quái vật cố gắng tìm đường ngắn nhất đến ngôi nhà của bạn. Cố gắng kiếm vàng bằng cách tiêu diệt địch và mua loại tháp phù hợp để đạt level cao nhất.

## Video trải nghiệm game và trình bày qua về code
- Link youtube: **https://youtu.be/jVeAYhro-HM**

- [0. Cách tải game](#0-cách-tải-game)
  * [a. Cách 1: Không bao gồm code.](#a-cách-1-không-bao-gồm-code)
  * [b. Cách 2: Bao gồm code và có thể biên dịch.](#b-cách-2-bao-gồm-code-và-có-thể-biên-dịch)
- [1.    Bắt đầu game](#1bắt-đầu-game)
- [2.     Các thành phần trong game:](#3-các-thành-phần-trong-game)
- [3.     Cách chơi](#4-cách-chơi)
  * [a.   Các loại Tower](#acác-loại-Tower)
  * [b.   Các loại Enemy](#bcác-loại-Enemy)
- [4. Chiến thắng và thất bại](#5-chiến-thắng-và-thất-bại)
- [Về đồ họa của game:](#về-đồ-họa-của-game)
- [Về source code game](#về-source-code-game)



# 0. Cách tải game
## a. Cách 1: Không bao gồm code.
- Tải game (được nén thành .zip) tại link sau: **https://github.com/dinhvanit/War_Defense/releases**.
- Cách này tiết kiệm bộ nhớ và thời gian tải đi rất nhiều (khoảng 103MB).
- Giải nén game vào một thư mục và bật TheInfernalTunnels.exe lên và chơi.

## b. Cách 2: Bao gồm code và có thể biên dịch.
- Bước 1: Clone repo này về hoặc chọn Code -> Download Zip.
- Tất cả code đều nằm trong thư mục src.
- Có thể nhảy đến bước 5 để chơi luôn
- Bước 2: Cài mingw. Ở đây tôi cài đặt phiên bản MinGW-W64 GCC-8.1. **x86_64-posix-seh**
- Một số chú ý:
- Nếu sử dụng trình biên dịch khác thì phải dịch lại icon: vào thư mục icon rồi dùng lệnh windres main.rc -O coff main.res trong cmd.
- Phải xóa ba dll của c++ trong thư mục chứa DemoGame.exe: `libgcc_s_seh-1.dll`, `libstdc++-6.dll`, `libwinpthread-1.dll`. Ba dll này chỉ dành cho người chơi không cài sẵn c++ trong máy.
- Bước 3: Cài GNU make.
- Bước 4: Mở cmd trong thư mục chứa Makefile và gõ lệnh make.
- Bước 5: Bật DemoGame.exe và chơi game.

# 1.	Bắt đầu game
Chạy vào bảng chọn menu có các lựa chọn cho mình

-`StartGame` ![]() : Bắt đầu game mới.
-`How to play` ![]() : Mở hướng dẫn chơi gồm từ điển Enemy và Tower, nhấn `back` 1[]() để trỏ lại main.
![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/Howtoplay.png)
-`Quit` ![]() : để thoát hoàn toàn game.

# 2.	 Các thành phần trong game:
-	Gold (Vàng) 
: là đơn vị để mua tháp phòng thủ, khởi đầu bằng một số Gold nhất định và sẽ nhận được khi tiêu diệt mỗi con quái hoặc bị quái xâm nhập nhà chính.
 
 - Heart (Tim) 
 : Số mạng của người chơi, đầu mỗi game bạn có mặc định một số mạng, và nếu bạn để quái xâm nhập vào nhà bạn sẽ bị trừ 1 tim mỗi một con quái, hết số Tim là bạn sẽ thua.

- Level (Cấp độ) ![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/star.png)
: Level của người chơi cũng như thành tích của ván đấu. Càng về level cao quái càng mạnh cần phải chiến thuật hợp lý.


-	TowerBar (Thanh tháp phòng thủ) ![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/StatusBar.png)
: hiển thị các tháp kèm thông số, có thể bấm vào hoặc nhấn phím tháp để chọn tháp. Ngoài ra còn chứa số vàng hiện tại `currentGold` và số tim hiện tại `currentHeart`.
 
-	TileBar (Thanh tiêu đề)
![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/Title.png)
: Bao gồm
- tên game (kèm tác giả là mình)
- `currentLevel` : level hiện tại.
- `currentType` : Tháp đang được lựa chọn.
- `NextEnemy` : Loại quái tiếp theo (hiện tại bản này có 1 loại nên chưa thêm chức năng).
- `UpdateTower` : Nâng cấp tháp (chưa update).
- `Quickly` : Tăng tốc (dễ nên sẽ update sau đó).
- `Pause` : Tạm dừng game và mở bảng chọn Pause
![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/menu.png)
  - Bật tắt nhạc nền hoặc âm thanh hiệu ứng
  - `Restart` chơi lại màn chơi
  - `Main Menu` quay trở lại menu
  - `Back to game` thoát bảng chọn pause và tiếp tục chơi game


 
# 4.	 Cách chơi
Đặt tháp tạo đường đi cho quái và tấn công quái, quái sẽ luôn tìm đường đi đến đích và sẽ mạnh dần theo thời gian. Vì vậy bạn phải đặt hợp lý các loại tháp để bảo vệ nhà bạn.

Thao tác chơi:
  -Chọn loại Tháp bằng các nút phím hoặc Bấm chuột trái vào thanh `TowerBar` để chọn loại mình muốn đặt, sau đó bấm chuột trái lên ô mình muốn đặt để đặt tháp.
  -Lưu ý : Sẽ KHÔNG ĐẶT ĐƯỢC tháp nếu nó chặn đường đi quái hoặc không đủ tiền mua loại tháp đó.
  -Hủy tháp: bấm chuột phải vào ô tháp bạn muốn hủy và hủy tháp (tuy nhiên sẽ chỉ hoàn lại `50%` sóo gold mua tháp đó cho bạn)

## a.	Các loại Tower
Có 5 loại cây, lần lượt theo thứ tự có thể nhận được trong game là:

||Tên tháp	|Chức năng|
|-|-|-|
|![image]()|Archer	|Mỗi lần bắn tia vào 1 con quái .|
|![image]()|Canon	|Gây sát thương tất cả mục tiêu nhưng sát thương yếu hơn Archer|
|![image]()|Mage	|Không gây sát thương nhưng làm chậm tất cả các quái trong tầm.|

 
## b.	Các loại Enemy
-	Có 1 loại Enemy:(chưa update thêm)

||Tên enemy 	|Chức năng|
|-|-|-|
|![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/bophai.png)|Cow	|Kêu và ăn cỏ, ngoài ra chỉ biết chạy và máu tăng theo level|

  
# 5. Chiến thắng và thất bại
- Không thắng được 


- Bạn sẽ thất bại nếu hết số tim

![image](https://raw.githubusercontent.com/dinhvanit/War_Defense/main/assets/images/defeatBoard.png)
`MENU` để trở lại menu
`RESTART` để chơi lại game
---
### Về đồ họa của game:
Về đồ họa em có lấy :
  Các phím sự kiện game: em cos tham khảo của anh Hiển : **https://github.com/nmhienbn/PVZ-Kaito-NMH-Edition/tree/main/resources/images**
  assets towers : game KingdomRush
  assets enemies và các phần khác em lấy trên mạng và edit bằng canva
Về Âm thanh em có lấy tại các bên :
**https://pixabay.com/vi/sound-effects/search/game/**
### Về source code game:
Em lấy ý tưởng game Bảo vệ cứ điểm (1 tựa game cũ trên Hệ điều hành Java)
Mã nguồn tham khảo: 
- Lazyfoo: **https://lazyfoo.net/tutorials/SDL/**
- Kênh Youtube: **https://www.youtube.com/watch?v=52ddOanCO6Y&list=PL1v1Rwp_7pRzmjGqrvj7umNz84EKfKmi0**
# Kết luận
- Đây là thành quả sau hơn 1 tháng đi tiếp thu kiến thức và tham khảo các bài làm trên youtube, web, từ mọi người.
- Em nhận thấy đã vận dụng những gì đã học trong môn nhập môn lập trình và lập trình nâng cao, ngoài ra trong quá trình làm game em đã học thêm được nhiều kiến thức và kĩ năng mới như : sử dụng thư viện đồ họa SDL2, tạo class đóng gói, kế thừa, đa hình (opp), các thuật toán như BFS, sử dụng linh hoạt các con trỏ thông minh, ...
- Đây sẽ là động lực, bước đệm để em có những bước phát triển tốt hơn trong sự nghiệp tương lai!

# EM XIN CẢM ƠN Ạ!!!