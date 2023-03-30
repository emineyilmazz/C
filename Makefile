/*
    * Make File
    * C dosyalarýný,  gcc komutu kullanarak main dosyasýna derletmeyi saðlayan fonksiyonlarý içerir.
    *  Birinci Proje
    * 10.12.2022
    * emine yilmaz  emine.yilmaz@stu.fsm.edu.tr
*/


all: main.c matrixLib.c
	gcc  main.c matrixLib.c -o main
