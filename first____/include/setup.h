// Файл где хранятся основные настройки прибора и подсчет входых данных с помощью препроцессорных директив
//-----------------Подключаемые библиотеки--------------------
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
LiquidCrystal_I2C lcd(0x27,16,2);
//---------------------------------------------------
typedef unsigned char byte; //это псевдонимы, вместо unsigned char (что долго писать и не отражает сути , нам не нужен символ, это будет просто
typedef unsigned int u_int ; //байт (8 бит) , которые мы не будем интерпретировать как символ, а просто как Байт
#define F_CPU 16000000// частота работы камня 16МГц в нашем случае
#define pusk_pin 6 // установка пина на котором будет висеть кнопка Пуск/Стоп
#define  set_pin 5 // пин кнопки установки режима (номера пинов от балды написал)
#define  opt_pin 2 //пин, к которому подключается оптопара
struct save_data
{
float time;
u_int count_open;
u_int count_close;
}
//#define Our_Timer TCCR2 //прога должна быть маштабируемой мы должны иметь возможность выбирать таймер TCCR2 например
//#ifdef TCCR2 
//#define T_setup 1<<CS101 //устанавливаем предделитель на 1024 ....Хотя правильнее сделать, чтоб в формуле проверки стояла частота камня и высчитичывалось какой нужен предделитель при заданной частоте
                         // и на основании этого выбирался бы предделитель , да еще и для каждого заданного счетчика в блоке ветвления
//#endif
// Этот файл можно рсширять, добавлять новые вводные данные 
//#define Int_OK TIMSK=1<<OCR1A // установку регистра состояния таймера написал об балды...
//Ну и так далее...Это основной установочный файл из которого будут браться основные параметры для функции setup() ардуино
#define Min_push 50 //убираем дребезг контактов, короче 50 мс нажаите не считается (бывают наводки на контакты и кратковременно на ноге может получаться высокий или нзкий сигнал)
#define Time_Hold 1000 // это время, после котрого преходим в режим зажима кнопки 
/*include <avr/io.h>
#include <avr/interrupt.h>
#define LEDPIN 13
/*
void setup()
{
    pinMode(LEDPIN, OUTPUT);

    // инициализация Timer1
    cli(); // отключить глобальные прерывания
    TCCR1A = 0; // установить TCCR1A регистр в 0
    TCCR1B = 0;

    // включить прерывание Timer1 overflow:
    TIMSK1 = (1 << TOIE1);
    // Установить CS10 бит так, чтобы таймер работал при тактовой частоте:
    TCCR1B |= (1 << CS10);

    sei();  // включить глобальные прерывания
}
// разрешаем прерывания
// произошло прерывание в обработчике прерывания считаем количество прокруток крыльчатки  */
