/*
    * Make File
    * C dosyalar�n�,  gcc komutu kullanarak main dosyas�na derletmeyi sa�layan fonksiyonlar� i�erir.
    *  Birinci Proje
    * 10.12.2022
    * emine yilmaz  emine.yilmaz@stu.fsm.edu.tr
*/


all: main.c matrixLib.c
	gcc  main.c matrixLib.c -o main
