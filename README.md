* Game dựa trên cảm hứng của Game Contra huyền thoại.

* Mã nguồn được viết bằng ngôn ngữ C++ đồ họa SDL 2.0.

* Nhiệm vụ: Hoàn thành thử thách bằng các lấy được Soul Stones ở cuối con đường. Trên con đường ấy, anh hùng chỉ được giới hạn số lượng đạn và phải tìm cách vượt qua các quái vật, thu thập phần thưởng suốt quãng được để được tăng số lượng đạn.

* Đăc biệt của Game:
  - Game tính giờ, mỗi lần chết nhân vật sẽ được đưa về vị trí ban đầu.
  - Lối chơi đơn giản, thao tác dễ dàng.
  - Giới hạn lượng đạn tấn công giúp GamePlay da dạng hơn.
  - Sự dụng hình ảnh, âm thanh tự tạo và re-edit từ interner.

* Các đối tượng trong game
  - Nhân vật với 3 loại đạn với công năng khác nhau.
  - Dối tượng quái vật : Boss được sinh random và có thể tự tấn công bao gồm: Boss cố định, Boss di chuyển trên mặt đất, Boss di chuyển trên không.
  - Sử dụng SDL_Image, SDL_TTF, SDL_Mixer, SDL_2_0.

* Các class trong game:

  - CommonFunction: Lớp chứa các thuộc tính chung về game ( Chiều dài, chiều rộng khung hình, FPS,...) , các hàm, biến khởi tạo ban đầu( Map, GamePlay nhận vật,...)
  - BaseObject: Đối tượng tổng định hình về Load hình ảnh, Render hình ảnh , các đối tượng sau đều kế thừa từ đối tượng này.
  - MainObject: Kế thừa từ BaseObject, cấu hình và điều khiển nhân vật chính:
    + LoadImg, show_clips, Show : Hiển thị hình ảnh của nhân vật qua các thao tác, ảnh động được chay từ 8 frames .
    + HandleInputAction: Điều khiển nhận vật qua thao tác người chơi: Mouse, Keyboard.
    + DoPlayer: Điều khiển nhân vật kết hợp cùng MOveonMap và CheckMap.
    + MoveOnMap: di chuyển khung hình theo Map mà nhân vật đi.
    + CheckMap: kiểm tra địa hình mà nhận vật đi qua.
    + HandleAttackObject: Điều khiển tầm xa đạn bắn.
    + RemoveAttack: Xóa đạn khi trúng mục tiêu.
  
  - ThreatsObject: Tương tự MainObject nhưng quản lý các đối tượng quái vật.
    + ImpMoveType: Quản lý từng trạng thái của quái vật.
  - GameMap: Quản lý MapGame
    + LoadMap: Đọc thông tin về sơ đồ Map từ file TEXT;
    + LoadTiles: Load hình ảnh cho từng ô nhỏ map đã chia.
    + DrawMap : Vẽ Map bằng hình ảnh
  - AttackObject:Quản lý hướng tấn công và loại đạn của nhân vật và quái vật.
  - Colliosion: Class riêng biệt về xử lý va chạm giữa các đối tượng.
  - ImpTimer: Quản lý thời gian và xử lý thêm về FPS game.
  - MenuGame: Quản lý MEnuGame và các màn chơi.
  - TextObject: Lớp có chức năng load text lên screen.
