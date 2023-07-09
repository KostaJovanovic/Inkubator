# Inkubator

Cilj projekta je izrada i programiranje inkubatora koji može da menja i održava temperaturu i vlažnost unutrašnjosti, za različite organizme i svrhe, na željeno vreme.

## Ideja 

Inkubator je planiran da izgleda kao mala rerna, sa staklom na vratima kako bi moglo da se gleda unutra (uglavnom jer je jako kul)

Glavna ideja projekta je da za početak napravimo funkcionalni inkubator za mikroorganizme i biljke. Kontrolisaće ga Arduino. Cilj je da korisnici mogu da naprave i čuvaju svoja podešavanja (neka vrsta preset-a) koja su koristili u različitim uslovima i za različite stvari. Ideju smo dobili jer smo hteli da radimo zajedno na međuseminarskom projektu, a inkubator je bio najbolja ideja. Želim da se u ovom projektu bavim automatizacijom, da učinim korišćenje inkubatora što jednostavnijim, bez gubitka različitih funkcija.

Inkubator će koristiti dva DHT11 senzora za vlagu i temperaturu, grejače iz postolja 3d printera u podu i plafonu. Za kontrolisanje vlažnosti bih kotistio nešto [ovako](https://circuitdigest.com/microcontroller-projects/diy-automatic-portable-humidifier-using-arduino).

Cilj mi je da napravim sličan sistem za kontrolisanje kao što ima [Ender-5 printer](https://youtu.be/Ho8_NnFE0b0?t=184). Specifično se odnosi na jedno dugme koje može da se okreće ali i klikće.

Takođe, da postoji sistem čuvanja i pravljenja preset-a, koji bi se prebacivali na inkubator preko usb-a ili kabla povezanog za telefon. Trenutna ideja mi je da preset bude u obliku `ime preseta; vreme; temperatura; vlažnost; šta je u inkubatoru; ime osobe koja stavlja` u .txt formatu.

Treba da ima UV lampu za dezinfekciju, pošto ostali načini (visoka temperatura / ručno čišćenje) nisu izvodljivi ili dovoljno konzistentni.

## Rađeno na "zimskom" seminaru

  Koristio sam Arduino Uno, dht11 senzor za toplotu i vlažnost vazduha. Prva prepreka na koju sam naišao je da sam senzor nije imao nikakav indikator ni koji je model, niti koji pin mu za šta služi.
  Ovo je problem zato što na njemu samom ne piše ni napon na kom radi, niti gde mu je uzemljenje / signal / napajanje
  Postoje mnogi tutoriali i uputstva na internetu, ali čak i oni koji pišu da su za DHT11, koriste DHT22 (u suštini isti senzor, ali DHT22 ima četiri, drugačije raspoređena pina, radi na drugačijem naponu, i koristi druge biblioteke.
  Sa ovime sam se borio duže nego što bih voleo da priznam, jer se na kraju ispostavilo da je i proto-ploča bila delimično neispravna

  Kada sam sredio sve sa senzorom, prešao sam na brojenje vremena. Posle nekoliko neuspelih pokušaja da arduino dobije tačno vreme, rukovodioc mi je spomenuo funkciju `millis()` sa kojom sam prolazio kroz agoniju do kraja dana. Većina mikrokontrolera ima unutrašnji brojač koji meri milisekunde koje su prošle otkako je krenuo da radi. Ta `millis()` funkcija pokupi informacije o vremenu i dozvoljava nam da sa njima radimo šta god nam zatreba.
  Evo primera:
  
```
void setup() {
  Serial.begin(9600);
}
void loop() {
  serial.print("Prošlo je ");
  int vreme = millis()/1000;
  serial.print(vreme);
  serial.println(" sekundi.")
  delay(5000);
}
```
  Ovim kodom, svakih 5 sekundi će arduino ispisati koliko je sekundi prošlo od početka, i mislio sam da sam sve rešio što se toga tiče.

  Problem je nastao kada je počeo da mi broji vreme unazad. Posle desetak sekundi, dobijao sam da je od početka prošlo oko "-30" sekundi po njegovoj računici. `milis()` u teoriji može da broji oko 50 dana pre nego što pređe preko integer limita i vrati se na početak. Ovaj problem je napravila samo jedna linija koda. `int vreme = millis()/1000;`

  Obična integer promenljiva, koja mi je u ovom slučaju bila vreme, ima kapacitet od 16 bita, što je raspon između `-32,768` i `32,767`. Korišćenjem `long int` umesto samo `int` se ovaj problem popravio, jer long int ima kapacitet od 32 bita, što je od `-2,147,483,648` do `2,147,483,648`. Ludo.

  Nakon što sam se izborio sa ovim nepredviđenim problemima, počeo sam da razmnatram načine na koje bih mogao da napravim sam inkubator.

  
Na seminaru se nisam bavio direktno inkubatorom, koliko sam istraživao kako radi arduino, koje su mu limitacije, kao i kako se koristi generalno, jer mi je iskustvo s njim bilo do nivoa paljenja i gašenja dioda, što ne mogu reći da je dovoljno za inkubator.

## Planovi za dalji rad

Za sada, arduino samo prikuplja podatke o temperaturi, vlažnosti i vremenu. Treba napraviti način da prihvati željenu temperaturu i vlažnost, i onda da ih održava određeno vreme. Takođe, naći način da sepoveže na humidifier i grejalice i da ih kontroliše. Najveći problem će stvarati sistem povratne sprege.

## Spisak komponenata 

(07.07.2023) [ovde](https://github.com/KostaJovanovic/Inkubator/blob/main/spisak_komponenata_2.xlsx)



## Problemi

Predvidivi problemi su:
- [ ] Kalibracija sistema povratne sprege
- [ ] Nameštanje sistema sa presetima
- [ ] Komunikacija samog inkubatora sa korisnikom (kako javlja da je došlo do greške / da je završio / da je unutrašnja temperatura došla do određenog nivoa itd). Trenutno je cilj da to radi preko piezoelektričnih zvučnika i dioda različitih boja, al blago rečeno, malo mi klimavo to.



Petnički projekat 2023 :tm:
