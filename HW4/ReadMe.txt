1. Program �al��t�r�ld���nda s�ras�yla 5 farkl� oyunu ba�lat�r ve ilk ayarlamalar� yapman�z� ister.

2. Do you wanna change Board Size? diye sorar. 'y' veya 'Y' yazarsan�z tahta boyutunu
   ayarlayabilece�iniz bir ekran gelir. Ba�ka bir harf tu�larsan�z mevcut tahta boyutuyla 
   devam eder.

3. Daha sonras�nda Current GameType: t olarak oyun tipini g�sterir.
   t = iki ki�ilik oyun, c = vs COM anlam�ndad�r.
   Do you wanna play default GameType? diye sorar. 'y' veya 'Y' yazarsan�z mevcut oyun
   tipiyle oynamaya ba�lars�n�z. Oyun tipini de�i�tirmek i�in ba�ka bir harf tu�lay�n.

4. Kullan�c�dan hareket giri�i almaya geldi�inde;
   A 1, B 3, C 6, D 12 gibi hareketler girilmelidir. K���k-b�y�k harf duyarl�d�r ve arada bo�luk
   olmal�d�r. a1, B3 gibi hareketler girince hata al�rs�n�z.
   Bunlara ek olarak oyunu kaydetmek i�in SAVE DOSYA�SM�.TXT yazarak oyunu kaydedebilirsiniz.
   Oyunu bir dosyadan y�klemek i�in de LOAD DOSYA�SM�.TXT yazarak oyunu y�kleyebilirsiniz.
   UNDO yaz�ld���nda oynanan hareketler geri al�nabilir.
   EARLYSTOP yazarak oyunu erkenden bitirebilirsiniz.

5. Oyunun i�leyi�i �u �ekildedir; �ncelikle 5 farkl� oyun s�ras�yla ba�lat�l�r ve ilk ayarlamalar�
yapman�z istenir(tahta boyutu, oyun tipi). Oyunlar s�ral� �ekilde oynan�r, ilk olarak user1(veya COM) 
hareketlerini ger�ekle�tirir b�t�n oyunlarda user1 hareketi yap�ld���nda user2 hareketine ge�er.
O an oynanan oyun ekranda g�sterildi�i i�in hangi oyunu oynad���n�z� anlayabilirsiniz.
SAVE DOSYA�SM�.TXT, LOAD DOSYA�SM�.TXT, UNDO, EARLYSTOP komutlar� da birer hareket yerine ge�ti�i i�in i�lem tamamland�ktan sonra
di�er oyundaki ad�ma ge�er. �rnek olarak hex1 oyunu oynan�rken SAVE komutunu kulland���n�zda oyun save
edilir ve s�radaki oyundaki i�lemden devam eder. Ayn� �ekilde hex1 oyunu oynan�rken herhangi bir oyun
LOAD edilirse load i�lemi tamamlan�r ve s�radaki oyundaki i�lemden devam eder. LOAD edilmi� oyunu
s�ra hex1 oyununa geldi�inde g�rebilirsiniz. UNDO komutu ger�ekle�tirildi�inde de ayn� �eyler ge�erlidir.
EARLYSTOP komutu yaz�larak oyunun erkenden bitirilmesi sa�lanabilir. Her iki oyuncu i�in de bir skor hesaplan�r.
Oyunda en uzun yolu olu�turan oyunu kazanan olur. E�er yol uzunluklar� e�it ise iki oyuncudan biri rastgele olarak
se�ilir ve kazanan o olur.
   
