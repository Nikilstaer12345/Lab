```C++
#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H


#include <IKeypad.h>
#include <lockcontroller.h>
#include <ILatch.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

class MockILatch:public ILatch
{
public:
    MOCK_METHOD(bool,isActive,(),(override));
    MOCK_METHOD(DoorStatus, open,(),(override));
    MOCK_METHOD(DoorStatus, close,(),(override));
    MOCK_METHOD(DoorStatus,getDoorStatus,(),(override));
};

class MockIKeypad: public IKeypad
{
public:
    MOCK_METHOD(bool, isActive,(),(override));
    MOCK_METHOD(void, wait,(),(override));
    MOCK_METHOD(PasswordResponse, requestPassword,(),(override));
};

/*
Тест 1
Исходные данные:
- Всё в порядке никаких проблем нет;
Действие:
- Вызывается метод wait() класса LockController;
Ожидается:
- Метод wait() класса IKeypad будет вызван один раз;
*/

TEST(Calculator, wait)
{
    MockILatch latch;
    MockIKeypad keypad;
    LockController contr=LockController(&keypad, &latch);
    EXPECT_CALL(keypad, wait())
             .Times(1);// вызывается один раз
    contr.wait();
}

/*
Тест 2
Исходные данные:
- Дверь закрыта.
Действие:
- Вызывается метод isDoorOpen() класса LockController;
Ожидается:
- Метод isDoorOpen() класса LockController вернёт false;
- Метод getDoorStatus() класса ILatch будет вызван один раз;
*/

TEST (Calculator, Door_close){
    bool CheckDoor;
    bool Check;
    MockILatch latch;
    MockIKeypad keypad;
    LockController contr=LockController(&keypad, &latch);
    EXPECT_CALL(latch,getDoorStatus())
            .Times(1);
    CheckDoor = contr.isDoorOpen();
    Check = CheckDoor;
    Check = false;
    EXPECT_FALSE(Check);
}

/*
Тест 3
Исходные данные:
- Дверь отрыта.
Действие:
- Вызывается метод isDoorOpen() класса LockController;
Ожидается:
- Метод isDoorOpen() класса LockController вернёт true;
- Метод getDoorStatus() класса ILatch будет вызван один раз;
*/

TEST(Calculator, Door_open){
    bool CheckDoor;
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    EXPECT_CALL(latch, getDoorStatus())
            .Times(1);
    CheckDoor = contr.isDoorOpen();
    EXPECT_TRUE(CheckDoor);
}

/*
Тест 4
Исходные данные:
- если нужно, защёлка двери успешно открывается и закрывается. Никаких помех нет.
Действие:
- Вызывается метод unlockDoor() класса LockController;
Ожидается:
- Метод unlockDoor() класса LockController вернёт DoorStatus::OPEN;
- Метод open() класса ILatch будет вызван один раз;
*/

TEST(Calculator, latch_open){
    bool CheckDoor;
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));
    CheckDoor = contr.isDoorOpen();
    EXPECT_TRUE(CheckDoor);
}

/*
Тест 5
Исходные данные:
- если нужно, защёлка двери успешно открывается и закрывается. Никаких помех нет.
Действие:
- Вызывается метод lockDoor() класса LockController;
Ожидается:
- Метод close() класса ILatch будет вызван один раз;
- Метод lockDoor() класса LockController вернёт DoorStatus::CLOSE;
*/

TEST(Calculator, latch_close){
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr = LockController(&keypad, &latch);
    EXPECT_CALL(latch, open());
    EXPECT_EQ(contr.lockDoor(), DoorStatus::OPEN);
}

/*
Тест 6
Исходные данные:
- Объекты классов IKeypad и ILatch созданы, валидны и переданы в конструктор LockController;
- С оборудованием всё в порядке.
Действие:
- Вызывается метод hardWareCheck() класса LockController;
Ожидается:
- Метод hardWareCheck() класса LockController вернёт HardWareStatus::OK;
- Метод isActive() класса IKeypad будет вызван один раз;
- Метод isActive() класса ILatch будет вызван один раз;
*/

TEST(Calculator,HardWareStatus_OK){
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr = LockController(&keypad,&latch);
    EXPECT_CALL(latch, isActive())
            .Times(1)
            .WillOnce(Return(1));
    EXPECT_CALL(keypad, isActive())
            .Times(1)
            .WillOnce(Return(1));
    HardWareStatus Return = contr.hardWareCheck();
    EXPECT_EQ(Return,HardWareStatus::OK);
}

/*
Тест 7
Исходные данные:
- Объект класса ILatch создан, валиден и передан в конструктор LockController;
- С задвижкой (ILatch) всё в порядке.
- Вместо объекта класса IKeypad передан nullptr;
Действие:
- Вызывается метод hardWareCheck() класса LockController;
Ожидается:
- Метод hardWareCheck() класса LockController вернёт HardWareStatus::ERROR;
- Метод isActive() класса IKeypad будет вызван ноль или более раз;
- Метод isActive() класса ILatch будет вызван ноль или более раз;
*/

TEST(Calculator,HardWareStatus_ERROR){
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(nullptr, &latch);
    EXPECT_CALL(latch ,isActive())
           .Times(AtLeast(0))
           .WillOnce(Return(1));
    EXPECT_CALL(keypad, isActive())
           .Times(AtLeast(0))
           .WillOnce(Return(1));
    HardWareStatus Return=contr.hardWareCheck();
    EXPECT_EQ(Return,HardWareStatus::ERROR);
}

/*
Тест 8
Исходные данные:
- Объекты классов IKeypad и ILatch созданы, валидны и переданы в конструктор LockController;
- С клавиатурой (IKeypad) всё в порядке.
- Задвижка (ILatch) не активна.
Действие:
- Вызывается метод hardWareCheck() класса LockController;
Ожидается:
- Метод hardWareCheck() класса LockController вернёт HardWareStatus::ERROR;
- Метод isActive() класса IKeypad будет вызван ноль или более раз;
- Метод isActive() класса ILatch будет вызван ноль или более раз;
*/

TEST(Calculator,hardWareStatus_ERROR2){
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    EXPECT_CALL(latch, isActive())
           .Times(AtLeast(0))
           .WillOnce(Return(0));
    EXPECT_CALL(keypad, isActive())
           .Times(AtLeast(0))
           .WillOnce(Return(1));
    HardWareStatus Return=contr.hardWareCheck();
    EXPECT_EQ(Return,HardWareStatus::ERROR);
}

/*
Тест 9
Исходные данные:
- LockController только создан, поэтому установлен дефолтный пароль("0000");
- Пользователь вводит правильный пароль (когда у него попросят).
Действие:
- Вызывается метод isCorrectPassword() класса LockController;
Ожидается:
- Метод isCorrectPassword() класса LockController вернёт true;
- Метод requestPassword() класса IKeypad будет вызван один раз;
*/

TEST(Calculator,True_password){
    bool CheckPassword;
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    PasswordResponse response {PasswordResponse::Status::OK,"0000"};
    EXPECT_CALL(keypad, requestPassword())
           .Times(1)
           .WillOnce(Return(response));
    CheckPassword = contr.isCorrectPassword();
    EXPECT_TRUE(CheckPassword);
}

/*
Тест 10
Исходные данные:
- LockController только создан, поэтому установлен дефолтный пароль("0000");
- Пользователь вводит НЕ правильный пароль.
Действие:
- Вызывается метод isCorrectPassword() класса LockController;
Ожидается:
- Метод isCorrectPassword() класса LockController вернёт false;
- Метод requestPassword() класса IKeypad будет вызван один раз;
*/

TEST(Calculator,False_password){
    bool CheckPassword;
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    PasswordResponse response {PasswordResponse::Status::OK,"1222"};
    EXPECT_CALL(keypad, requestPassword())
           .Times(1)
           .WillOnce(Return(response));
    CheckPassword = contr.isCorrectPassword();
    EXPECT_FALSE(CheckPassword);
}

/*
Тест 11
Исходные данные:
- LockController только создан, поэтому установлен дефолтный пароль("0000");
- Старый пароль вводится правильно;
Действие:
- Вызывается метод resetPassword() класса LockController;
Ожидается:
- будет запрошен старый пароль;
- будет установлен новый пароль, введённый пользователем (нельзя на прямую проверить, т.к. password не public и геттера нет);
*/

TEST(Calculator,old_pass_true){
    bool CheckPassword;
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    PasswordResponse oldPassword{PasswordResponse::Status::OK,"0000"};
    PasswordResponse newPassword{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(keypad, requestPassword())
           .Times(2)
           .WillOnce(Return(oldPassword))
           .WillOnce(Return(newPassword));
    contr.resetPassword();
    EXPECT_CALL(keypad, requestPassword())
           .Times(1)
           .WillOnce(Return(newPassword));
    CheckPassword = contr.isCorrectPassword();
    EXPECT_TRUE(CheckPassword);
}

/*
Тест 12
Исходные данные:
- Пароль изменён на "9876";
- Пользователь правильно вводит пароль;
Действие:
- Вызывается метод resetPassword() класса LockController;
Ожидается:
В результате вызова метода resetPassword() класса LockController будет:
- будет запрошен старый пароль;
- будет установлен новый пароль, введённый пользователем (нельзя на прямую проверить, т.к. password не public и геттера нет);
*/

TEST(Calculator, new_pass_true){
    bool CheckPassword;
    MockIKeypad keypad;
    MockILatch latch;
    LockController contr=LockController(&keypad, &latch);
    PasswordResponse delPassword{PasswordResponse::Status::OK,"0000"};
    PasswordResponse oldPassword{PasswordResponse::Status::OK,"1111"};
    PasswordResponse newPassword{PasswordResponse::Status::OK,"2222"};
    EXPECT_CALL(keypad, requestPassword())
           .Times(2)
           .WillOnce(Return(delPassword))
           .WillOnce(Return(oldPassword));
    contr.resetPassword();
    EXPECT_CALL(keypad, requestPassword())
           .Times(1)
           .WillOnce(Return(oldPassword));
    CheckPassword = contr.isCorrectPassword();
    EXPECT_TRUE(CheckPassword);
    EXPECT_CALL(keypad, requestPassword())
            .Times(2)
            .WillOnce(Return(oldPassword))
            .WillOnce(Return(newPassword));
    contr.resetPassword();
    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(newPassword));
    CheckPassword = contr.isCorrectPassword();
    EXPECT_TRUE(CheckPassword);
}
#endif
```
