/*
 * SDカード読み取り専用、東雲フォントライブラリサンプルスケッチ
 * 予めSDカードにfontフォルダを作成しておき、以下のファイルをコピーしておく
 * Utf8Sjis.tbl (UTF-8 Shift_JIS変換テーブル)
 * shnmk16.bdf (全角東雲フォント)
 * shnm8x16.bdf (半角東雲フォント)
 */
 
#include <SD_ShinonomeFNT_Pack.h>
 
/*
 sclk = 14;
 mosi = 13; //Master Output Slave Input ESP8266=Master
 miso = 12; //Master Input Slave Output
*/
 
const uint8_t cs_SD = 5;
 
const char* UTF8SJIS_file = "font/Utf8Sjis.tbl"; //UTF8 Shift_JIS 変換テーブルファイル名
const char* Shino_Zen_Font_file = "font/shnmk16.bdf"; //全角東雲フォントファイル名を定義
const char* Shino_Half_Font_file = "font/shnm8x16.bdf"; //半角東雲フォントファイル名を定義
void Serial_Monitor_Dot_Display(uint16_t Len, uint8_t font_buf[][16]);
 
enum { MaxTxt = 16 }; //MaxTxt = 文字列の最大数（半角数）
 
SD_ShinonomeFNT_Pack SFR (cs_SD, MaxTxt); //東雲フォントクラス定義
 
uint8_t Sino_font_buf[MaxTxt][16]; //東雲（しののめ）フォントバッファ
uint16_t sj_length; //Shift_JISコードのバイト数
 
void setup() {
  String str1 = "東雲日本語漢字";
  String str2 = "こんにちは";
   
  Serial.begin(115200);
  Serial.println();
  //東雲フォントライブラリ初期化
  SFR.SD_Shinonome_Init(UTF8SJIS_file, Shino_Half_Font_file, Shino_Zen_Font_file);
 
  sj_length = SFR.ShinonomeFNTread_ALL(str1, Sino_font_buf); //東雲フォント一括変換
  Serial_Monitor_Dot_Display(sj_length, Sino_font_buf); //シリアルモニターにドット表示
    
  uint8_t sj_code[MaxTxt];
  sj_length = SFR.SjisShinonomeFNTread_ALL(str2, sj_code, Sino_font_buf); //文字列のShift_JISコードと、東雲フォント両方を取得
  Serial_Monitor_Dot_Display(sj_length, Sino_font_buf); //シリアルモニターにドット表示
 
  //取得したShift_JISコードバイト数とコードをシリアルモニターに表示
  Serial.print("str2 Shift_JIS bytes = ");
  Serial.println(sj_length);
  Serial.print("str2 = ");
  for(int i=0; i<sj_length; i++){
    Serial.write(sj_code[i]);
  }
}
 
void loop() {
}
 
void Serial_Monitor_Dot_Display(uint16_t Len, uint8_t font_buf[][16]){
  int i, j, k;
 
  for(i=0; i<16; i++){
    for(j=0; j<Len; j++){
      for(k=7; k>=0; k--){
        if(bitRead(font_buf[j][i], k) == 1){
          Serial.print('*');
        }else{
          Serial.print(' ');
        }
      }        
    }
    Serial.println();
  }
}