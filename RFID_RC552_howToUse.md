Mô tả các hàm và các hằng số trong thư viện:
1. Các hằng số:
    -> MI_OK, MI_NOTAGERR, MI_ERR: Các giá trị enum đại diện cho trạng thái trả về của các hàm trong thư viện.
    -> MFRC522_CS_LOW, MFRC522_CS_HIGH: Điều khiển chân CS (Chip Select) để chọn hoặc bỏ chọn module RC522.

2. Các hằng số lệnh (commands) của module RC522:
    -> PCD_IDLE, PCD_AUTHENT, PCD_RECEIVE, PCD_TRANSMIT, PCD_TRANSCEIVE, PCD_RESETPHASE, PCD_CALCCRC: Các lệnh điều khiển module RC522.
    -> PICC_REQIDL, PICC_REQALL, PICC_ANTICOLL, PICC_SElECTTAG, PICC_AUTHENT1A, PICC_AUTHENT1B, PICC_READ, PICC_WRITE, PICC_DECREMENT,      PICC_INCREMENT, PICC_RESTORE, PICC_TRANSFER, PICC_HALT: Các lệnh tương tác với thẻ Mifare_One.

3. Các thanh ghi (registers) của module RC522:
    -> Các thanh ghi được liệt kê theo địa chỉ trong bộ nhớ của module RC522.
4. Cấu trúc MFRC522_Name:
Đây là một cấu trúc dùng để lưu trữ thông tin về module RC522, bao gồm SPI, GPIO và CS_PIN.
    -> SPI: Con trỏ đến cấu trúc SPI_HandleTypeDef, đại diện cho kết nối SPI.
    -> CS_PORT: Địa chỉ của thanh ghi GPIO điều khiển chân CS.
    -> CS_PIN: Chân CS.
5. Các hàm chính trong thư viện:

    -> MFRC522_Init: Khởi tạo module RC522 với thông tin được đưa vào cấu trúc MFRC522_Name.
    -> MFRC522_Check: Kiểm tra xem module RC522 có sẵn thẻ không.
    -> MFRC522_Compare: So sánh CardID với CompareID.
    -> MFRC522_Request: Gửi yêu cầu tương tác với thẻ.
    -> MFRC522_ToCard: Gửi và nhận dữ liệu giữa module RC522 và thẻ.
    -> MFRC522_Anticoll: Thực hiện quá trình anti-collision để nhận diện các thẻ trong phạm vi.
    -> MFRC522_CalculateCRC: Tính toán mã kiểm tra CRC cho dữ liệu được cung cấp.
    -> MFRC522_SelectTag: Chọn thẻ có số seri (serNum) đã cho.
    -> MFRC522_Auth: Xác thực với thẻ sử dụng khóa (Sectorkey) và số seri (serNum) đã cho.
    -> MFRC522_Read: Đọc dữ liệu từ khối (block) trên thẻ.
    -> MFRC522_Write: Ghi dữ liệu vào khối (block) trên thẻ.
    -> MFRC522_Halt: Đặt module RC522 vào trạng thái ngủ(tam dừng module).
-> Đây là các hàm cung cấp các chức năng cơ bản để tương tác với module RC522 và thẻ RFID Mifare_One. 
-> Thư viện này sử dụng để điều khiển module RC522 trên vi điều khiển STM32F4 và thực hiện các thao tác đọc/ghi dữ liệu trên thẻ RFID.

===============================================================================================================================================
Cách sử dụng các hàm trong thư viện:
Dưới đây là các hàm và giải thích về các đối số của từng hàm trong thư viện:

1. `void MFRC522_Init(MFRC522_Name* MFRC522, SPI_HandleTypeDef* SPI_In, GPIO_TypeDef* CS_PORT, uint16_t CS_PIN)`: Hàm này được sử dụng để khởi tạo module RC522. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `SPI_In`: Con trỏ đến cấu trúc SPI_HandleTypeDef để sử dụng giao tiếp SPI.
   - `CS_PORT`: GPIO_TypeDef, đại diện cho thanh ghi GPIO của chân chip select.
   - `CS_PIN`: Số chân của chip select.

2. `MFRC522_Status_t MFRC522_Check(MFRC522_Name* MFRC522, uint8_t* id)`: Hàm này được sử dụng để kiểm tra sự tồn tại của một thẻ RFID RC522. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `id`: Một mảng 5 byte để lưu ID của thẻ được phát hiện.

3. `MFRC522_Status_t MFRC522_Compare(MFRC522_Name* MFRC522, uint8_t* CardID, uint8_t* CompareID)`: Hàm này được sử dụng để so sánh ID của thẻ với một ID khác. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `CardID`: Một mảng 5 byte chứa ID của thẻ cần so sánh.
   - `CompareID`: Một mảng 5 byte chứa ID để so sánh với ID của thẻ.

4. `MFRC522_Status_t MFRC522_Request(MFRC522_Name* MFRC522, uint8_t reqMode, uint8_t* TagType)`: Hàm này được sử dụng để gửi yêu cầu cho thẻ RFID để xác định loại thẻ. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `reqMode`: Chế độ yêu cầu (VD: PICC_REQIDL - tìm vùng anten không vào chế độ hibernation).
   - `TagType`: Con trỏ đến biến để lưu loại thẻ được xác định.

5. `MFRC522_Status_t MFRC522_ToCard(MFRC522_Name* MFRC522, uint8_t command, uint8_t* sendData

, uint8_t sendLen, uint8_t* backData, uint16_t* backLen)`: Hàm này được sử dụng để giao tiếp với thẻ RFID. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `command`: Lệnh gửi đến thẻ RFID (VD: PCD_AUTHENT - xác thực khóa).
   - `sendData`: Mảng dữ liệu gửi đến thẻ RFID.
   - `sendLen`: Độ dài dữ liệu gửi đến thẻ RFID.
   - `backData`: Mảng dữ liệu được trả về từ thẻ RFID.
   - `backLen`: Con trỏ đến biến lưu độ dài dữ liệu trả về từ thẻ RFID.

6. `MFRC522_Status_t MFRC522_Anticoll(MFRC522_Name* MFRC522, uint8_t* serNum)`: Hàm này được sử dụng để thực hiện chức năng chống va chạm (anti-collision) khi có nhiều thẻ RFID trong phạm vi đọc. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `serNum`: Mảng 5 byte để lưu số serial của thẻ được xác định.

7. `void MFRC522_CalculateCRC(MFRC522_Name* MFRC522, uint8_t* pIndata, uint8_t len, uint8_t* pOutData)`: Hàm này được sử dụng để tính toán CRC cho dữ liệu. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `pIndata`: Mảng dữ liệu đầu vào.
   - `len`: Độ dài dữ liệu đầu vào.
   - `pOutData`: Mảng dữ liệu đầu ra sau khi tính toán CRC.

8. `uint8_t MFRC522_SelectTag(MFRC522_Name* MFRC522, uint8_t* serNum)`: Hàm này được sử dụng để chọn một thẻ RFID cụ thể để làm việc. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `serNum`: Mảng 5 byte chứa số serial của thẻ cần chọn.

9. `MFRC522_Status_t MFRC522_Auth(MFRC522_Name* MFRC522, uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum)`: Hàm này được sử dụng để xác thực khóa truy cập cho một khối dữ liệu cụ thể

 trên thẻ RFID. Các đối số của hàm bao gồm:
   - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
   - `authMode`: Chế độ xác thực (VD: PICC_AUTHENT1A - xác thực bằng khóa A).
   - `BlockAddr`: Địa chỉ khối dữ liệu cần xác thực.
   - `Sectorkey`: Mảng 6 byte chứa khóa truy cập cho khu vực của khối dữ liệu.
   - `serNum`: Mảng 5 byte chứa số serial của thẻ.

10. `MFRC522_Status_t MFRC522_Read(MFRC522_Name* MFRC522, uint8_t blockAddr, uint8_t* recvData)`: Hàm này được sử dụng để đọc dữ liệu từ một khối cụ thể trên thẻ RFID. Các đối số của hàm bao gồm:
    - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
    - `blockAddr`: Địa chỉ khối dữ liệu cần đọc.
    - `recvData`: Mảng 16 byte để lưu dữ liệu đọc được từ khối trên thẻ RFID.

11. `MFRC522_Status_t MFRC522_Write(MFRC522_Name* MFRC522, uint8_t blockAddr, uint8_t* writeData)`: Hàm này được sử dụng để ghi dữ liệu vào một khối cụ thể trên thẻ RFID. Các đối số của hàm bao gồm:
    - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
    - `blockAddr`: Địa chỉ khối dữ liệu cần ghi.
    - `writeData`: Mảng 16 byte chứa dữ liệu cần ghi vào khối trên thẻ RFID.

12. `void MFRC522_Halt(MFRC522_Name* MFRC522)`: Hàm này được sử dụng để dừng hoạt động của thẻ RFID. Các đối số của hàm bao gồm:
    - `MFRC522`: Con trỏ đến cấu trúc MFRC522_Name chứa thông tin về module RC522.
