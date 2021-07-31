1. Program çalýþtýrýldýðýnda sýrasýyla 5 farklý oyunu baþlatýr ve ilk ayarlamalarý yapmanýzý ister.

2. Do you wanna change Board Size? diye sorar. 'y' veya 'Y' yazarsanýz tahta boyutunu
   ayarlayabileceðiniz bir ekran gelir. Baþka bir harf tuþlarsanýz mevcut tahta boyutuyla 
   devam eder.

3. Daha sonrasýnda Current GameType: t olarak oyun tipini gösterir.
   t = iki kiþilik oyun, c = vs COM anlamýndadýr.
   Do you wanna play default GameType? diye sorar. 'y' veya 'Y' yazarsanýz mevcut oyun
   tipiyle oynamaya baþlarsýnýz. Oyun tipini deðiþtirmek için baþka bir harf tuþlayýn.

4. Kullanýcýdan hareket giriþi almaya geldiðinde;
   A 1, B 3, C 6, D 12 gibi hareketler girilmelidir. Küçük-büyük harf duyarlýdýr ve arada boþluk
   olmalýdýr. a1, B3 gibi hareketler girince hata alýrsýnýz.
   Bunlara ek olarak oyunu kaydetmek için SAVE DOSYAÝSMÝ.TXT yazarak oyunu kaydedebilirsiniz.
   Oyunu bir dosyadan yüklemek için de LOAD DOSYAÝSMÝ.TXT yazarak oyunu yükleyebilirsiniz.
   UNDO yazýldýðýnda oynanan hareketler geri alýnabilir.
   EARLYSTOP yazarak oyunu erkenden bitirebilirsiniz.

5. Oyunun iþleyiþi þu þekildedir; öncelikle 5 farklý oyun sýrasýyla baþlatýlýr ve ilk ayarlamalarý
yapmanýz istenir(tahta boyutu, oyun tipi). Oyunlar sýralý þekilde oynanýr, ilk olarak user1(veya COM) 
hareketlerini gerçekleþtirir bütün oyunlarda user1 hareketi yapýldýðýnda user2 hareketine geçer.
O an oynanan oyun ekranda gösterildiði için hangi oyunu oynadýðýnýzý anlayabilirsiniz.
SAVE DOSYAÝSMÝ.TXT, LOAD DOSYAÝSMÝ.TXT, UNDO, EARLYSTOP komutlarý da birer hareket yerine geçtiði için iþlem tamamlandýktan sonra
diðer oyundaki adýma geçer. Örnek olarak hex1 oyunu oynanýrken SAVE komutunu kullandýðýnýzda oyun save
edilir ve sýradaki oyundaki iþlemden devam eder. Ayný þekilde hex1 oyunu oynanýrken herhangi bir oyun
LOAD edilirse load iþlemi tamamlanýr ve sýradaki oyundaki iþlemden devam eder. LOAD edilmiþ oyunu
sýra hex1 oyununa geldiðinde görebilirsiniz. UNDO komutu gerçekleþtirildiðinde de ayný þeyler geçerlidir.
EARLYSTOP komutu yazýlarak oyunun erkenden bitirilmesi saðlanabilir. Her iki oyuncu için de bir skor hesaplanýr.
Oyunda en uzun yolu oluþturan oyunu kazanan olur. Eðer yol uzunluklarý eþit ise iki oyuncudan biri rastgele olarak
seçilir ve kazanan o olur.
   
