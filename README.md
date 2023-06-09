# Final_Project
目前預定於 6/12, 13 DEMO，DEMO 組別與期中相同，如果需要變更請聯繫助教改變分組名單

期末專題題目
以附件檔案中的選課資料為基礎，實作 indexing 機制進行選課查詢

附件檔案說明
DB_students.csv 為單純學號與課號之對應，請注意，學號有兩種格式 (長度不同)，另外兩個檔案在學號與課號之對應上與 DB_students 相同，差異在於加上了課程中文名稱，尾綴 big5 檔案的中文為 Big5 編碼、utf8 的則為 UTF-8 編碼

基本需求

(1) 實作資料 repository: 將原始資料檔案以 block 為單位切割分別儲存，單一 block 最多只能存放一百筆選課資料或上限 8KB 的索引資料，DEMO 時不需要展示分割 repository 的程式，僅需說明 repository 產生的方式即可；

(2) 以上述 repository 為基礎，製作 sequence index 進行選課查詢，輸入學號可以輸出該學號所選的所有課程之課號，輸入課號可以輸出該課號選課的所有學生之學號；

(3) 查詢部分如果使用 Python 實作，禁止使用 Pandas 或進階資料處理之套件。

完成基本需求，得分為 65 分

進階需求

(1) 輸出時包含中文課名；  
(2) 建立 中文課名 的 index，輸入中文課名時可以輸出該課程的選課學生，如有同名稱有多門課程 (課號不同，需分開顯示)；  
(3) 手刻/自行實作 hash index 實作上述任意屬性的 index (實作 hash index 可以不用實作 sequence index)；  
(4) 手刻/自行實作 balanced tree 實作上述任意屬性的 index (實作 balanced tree index 可以不用實作 sequence index  

(3)、(4) 請勿使用既有 library。
