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

+) kết quả = hình ảnh;
html+java+css

Mã hoá

<img width="763" height="817" alt="image" src="https://github.com/user-attachments/assets/d1f19e0c-7b0c-4658-b08e-08e2b6ea1c97" />

Giải mã

<img width="772" height="772" alt="image" src="https://github.com/user-attachments/assets/004e2d97-efcf-4c87-9881-599578c4be72" />

C++

mã hoá

<img width="396" height="448" alt="image" src="https://github.com/user-attachments/assets/f1c2427c-f4b0-450c-8011-4ab208f739dc" />

giải mã

<img width="378" height="415" alt="image" src="https://github.com/user-attachments/assets/edb29573-0bf3-4cc3-aa44-375adf48f007" />


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

+) kết quả = hình ảnh;
html+java+css

Mã hoá

<img width="828" height="841" alt="image" src="https://github.com/user-attachments/assets/7328a158-b8a4-4af7-aa89-4530b35aee1f" />

Giải mã

<img width="815" height="846" alt="image" src="https://github.com/user-attachments/assets/e67369f0-552e-4294-82be-250cc50f5182" />

C++

Mã hoá

<img width="377" height="473" alt="image" src="https://github.com/user-attachments/assets/7964d7ef-6ff3-47ec-89d2-c5cf00ef2f68" />

Giải mã 

<img width="394" height="442" alt="image" src="https://github.com/user-attachments/assets/c6bd32a6-3384-429c-9764-cb5178352324" />

3. Hoán vị / Transposition

Tên gọi

-Permutation cipher (cipher hoán vị / transposition cipher) — giữ nguyên ký tự nhưng thay đổi vị trí theo một hoán vị cố định.

Thuật toán

-Cách hoạt động:

+Chia plaintext (sau chuẩn hóa) thành các block độ dài n (padding nếu cần).

+Khoá là một hoán vị π trên {0,...,n-1}.

+Với mỗi block P[0..n-1], tạo block cipher C sao cho:

             C[π(i)]=P[i]

+Ghép các block mã hoá lại.

-Giải mã: áp dụng hoán vị nghịch đảo π^{-1} để phục hồi vị trí.

Không gian khoá

-Với block size n, số hoán vị = n!. Ví dụ: n=5 → 120; n=8 → 40,320. Với n lớn, không gian rất lớn.

Cách phá mã (không cần khoá)

1)Brute-force: chỉ khả thi nếu n nhỏ (thử tất cả n!).

2)Known-plaintext / crib: nếu biết mảnh plaintext, suy ra hoán vị cho block liên quan.

3)Phân tích vị trí / mẫu: dùng tần suất bigram/trigram qua các block, hoặc tìm các pattern (ví dụ chữ cái phân tán xuyên block).

4)Heuristic / hill-climbing: thuật toán tìm lời giải tốt nhất bằng tối ưu hoá (phổ biến trong mật mã học hiện đại)

+) kết quả = hình ảnh;
html+java+css

Mã hoá

<img width="759" height="679" alt="image" src="https://github.com/user-attachments/assets/218835ba-9898-4b35-abf7-1b06ee6be727" />

Giải Mã

<img width="786" height="682" alt="image" src="https://github.com/user-attachments/assets/b27e61de-dc0d-44f1-8436-afef2214a40e" />

C++

Mã hoá 

<img width="390" height="461" alt="image" src="https://github.com/user-attachments/assets/9339f864-a076-4186-8f13-f9fe95507395" />

Giải mã

<img width="396" height="443" alt="image" src="https://github.com/user-attachments/assets/9d740dfc-b28d-49df-adad-301ea0cb6b1c" />

4. Vigenère
Tên gọi

-Vigenère cipher — cipher đa bảng (polyalphabetic), dùng một chuỗi khóa lặp để dịch từng ký tự.

Thuật toán

-Tiền xử lý: A→0..Z→25; khóa K có độ dài L.

-Mã hoá: với vị trí i:

                            Ci​=(Pi​+KimodL​)mod26

        (với K_j là shift (0..25) từ ký tự khóa).

-Giải mã:

                           Pi​=(Ci​−KimodL​+26)mod26

Không gian khoá

- Với khóa độ dài L, không gian = 26^L. (Rất lớn nếu L lớn).

Cách phá mã (không cần khoá)

1)Kasiski test: tìm các n-gram (thường 3 ký tự) lặp xuất hiện trong cipher và lấy ƯCLN (gcd) các khoảng cách giữa các lần lặp — gợi ý độ dài khóa L.

2)Friedman test (Index of Coincidence): ước lượng độ dài khóa bằng IC; IC cao gần 0.066 (tiếng Anh) khi nhóm có cùng shift.

3)Sau khi biết L: chia cipher thành L nhóm (các ký tự cách nhau L), áp dụng phân tích tần suất trên từng nhóm để tìm shift từng nhóm (trở về bài Caesar cho mỗi nhóm).

4)Kỹ thuật brute-force: nếu L nhỏ hoặc danh sách khóa hạn chế, thử tất cả.

5)Known-plaintext / crib: dùng đoạn plaintext biết trước để suy khóa.

+) kết quả = hình ảnh;
html+java+css

Mã Hoá

<img width="809" height="779" alt="image" src="https://github.com/user-attachments/assets/70d0cabf-5571-4be3-b629-7d0a3891ed34" />

Giải mã

<img width="838" height="808" alt="image" src="https://github.com/user-attachments/assets/70ddd110-d2c2-4d43-8866-a6b9a0a48e0b" />

C++

Mã hoá

<img width="380" height="434" alt="image" src="https://github.com/user-attachments/assets/52497849-5cdb-42d9-adea-968d58ec0bf5" />

Giải mã

<img width="391" height="403" alt="image" src="https://github.com/user-attachments/assets/8d88b5d8-2c25-4d59-bbd8-11e0d6895ccc" />

5. Playfair
Tên gọi

-Playfair cipher — mã hoán vị digraph (mã theo cặp 2 ký tự) sử dụng ma trận 5×5 xây từ một khóa; do Charles Wheatstone đề xuất, phổ biến bởi Lord Playfair.

Thuật toán

-Chuẩn bị bảng 5×5:

1)Lấy khóa (ví dụ "MONARCHY"), loại chữ trùng, nối các chữ còn lại A–Z; thường gộp I/J thành một ô (thông dụng).

2)Điền ma trận 5×5 theo thứ tự từ khóa rồi các chữ còn lại.

-Chuẩn hoá plaintext:

1)Chuyển chữ hoa, thay J bằng I (nếu gộp).

2)Tạo digraph (cặp): nếu hai ký tự trong một cặp giống nhau, chèn X (hoặc chữ khác) giữa; nếu cuối cùng dư 1 ký tự, thêm X.

-Quy tắc mã hoá cho từng cặp (A,B):

1)Nếu A và B cùng hàng: thay bằng ký tự bên phải của mỗi chữ (vòng quanh).

2)Nếu A và B cùng cột: thay bằng ký tự bên dưới mỗi chữ (vòng quanh).

3)Nếu A và B không cùng hàng/cột: thay A bằng chữ nằm ở giao của hàng A và cột B; thay B bằng chữ ở giao của hàng B và cột A (tạo hình chữ nhật).

-Giải mã: làm ngược lại (bên trái / bên trên / đổi theo chữ nhật).

Không gian khoá

-Lượng bảng khả dĩ tương đương số hoán vị của 25 ký tự: 25! (rất lớn). Trong thực hành, không gian khoá do cách chọn khóa (dài ngắn) sẽ nhỏ hơn nhưng vẫn rất lớn.

Cách phá mã (không cần khoá)

1)Phân tích digraph: Playfair mã theo cặp nên tần suất digram (cặp chữ) bị thay đổi đặc trưng; so sánh với tần suất digram ngôn ngữ có thể cho manh mối.

2)Heuristic search / simulated annealing / hill-climbing: do không gian rất lớn, sử dụng thuật toán tối ưu hoá để tìm ma trận phù hợp với phân bố digram/ngôn ngữ (phương pháp phổ biến để phá Playfair).

3)Known-plaintext: nếu có một số cặp plaintext ↔ cipher biết trước, có thể dựng dần bảng.

4)Tấn công bằng từ điển: thử các khóa khả dĩ nếu khóa ngắn hoặc có cấu trúc từ vựng.

+) kết quả = hình ảnh;
html+java+css

Mã hoá 

<img width="833" height="722" alt="image" src="https://github.com/user-attachments/assets/e8d4854c-564f-4f0f-a63c-92305e76d322" />

Giải mã 

<img width="786" height="697" alt="image" src="https://github.com/user-attachments/assets/b5c95e1b-f019-4f67-89fb-ad70cdd24e2f" />

C++

Mã hoá 

<img width="394" height="453" alt="image" src="https://github.com/user-attachments/assets/72368b51-f28b-4dc9-8aed-ae676c66da94" />

Giải mã

<img width="361" height="413" alt="image" src="https://github.com/user-attachments/assets/1e2af494-a476-4d19-953c-d8f4d1002f4e" />

