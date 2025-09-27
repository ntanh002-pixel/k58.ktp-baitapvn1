# BÀI TẬP MÔN: An toàn và bảo mật thông tin
## BÀI TẬP 1:


Tên gọi
Thuật toán mã hoá, thuật toán giải mã
Không gian khóa
Cách phá mã (mà không cần khoá)
Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript

1. Caesar (Caesar cipher)
2. Tên gọi
Caesar cipher — đặt theo Julius Caesar; phương pháp đơn giản dịch mỗi ký tự theo một số vị trí cố định (shift cipher).
Thuật toán

--Tiền xử lý: chỉ xét chữ cái Latin (A–Z); thường chuyển về chữ hoa. Gán A→0, B→1, …, Z→25.

--Mã hoá: với mỗi ký tự p (mã số x ∈ 0..25) và khoá k (0..25):

                   E(x)=(x+k)mod26
                   
   (k là số vị trí dịch sang phải).
   
Giải mã: với c là mã số của chữ trong cipher:

                   D(c)=(c−k+26)mod26
                   
   (tương đương dịch ngược k vị trí).
   
Không gian khoá:

k ∈ {0,1,...,25} → 26 khả năng. (Thực tế chỉ 25 khác nhau nếu coi k=0 là vô hiệu).

Cách phá mã (không cần khoá)

--Brute-force: thử tất cả 26 khả năng — rất nhanh; chọn bản giải có nghĩa.

--Phân tích tần suất: tính tần suất chữ cái trong cipher, giả sử chữ xuất hiện nhiều nhất tương ứng chữ E (tiếng Anh) hoặc theo ngôn ngữ. Từ đó suy ra k.

--Known-plaintext / crib: nếu biết một mẩu plaintext xuất hiện, suy khoá ngay.

==> yếu, dễ bị hack

<img width="1343" height="374" alt="image" src="https://github.com/user-attachments/assets/2e8ed61d-dabf-4b1e-9f9b-fe4b99c7c98b" />

2. Affine cipher

Tên gọi

Affine cipher — biến thể tuyến tính của Caesar: kết hợp nhân và cộng modulo 26.

Thuật toán

Tiền xử lý: ánh xạ A→0..Z→25.

Mã hoá: chọn hai thông số khoá a và b với gcd(a,26)=1. Với ký tự x:

E(x)=(a⋅x+b)mod26

Giải mã: cần nghịch đảo modulo của a, kí hiệu a^{-1} sao cho a·a^{-1} ≡ 1 (mod 26).

D(y)=a−1⋅(y−b)mod26

Điều kiện

a phải nghịch đảo modulo 26 → gcd(a,26)=1. Giá trị a hợp lệ: {1,3,5,7,9,11,15,17,19,21,23,25} (12 giá trị).

Không gian khoá

|A| = 12 (số a hợp lệ) × |B| = 26 → 312 khả năng.

Cách phá mã (không cần khoá)

Brute-force: thử tất cả 312 cặp (a,b) và kiểm tra bản giải hợp lý.

Tần suất / known-plaintext: nếu biết phân bố tần suất hoặc một vài chữ plaintext → giải hệ tuyến tính nhỏ để tìm a và b.

Kỹ thuật cặp: dùng giả thiết rằng ký tự có tần suất cao nhất tương ứng E → suy cặp (a,b) bằng giải hai phương trình.
