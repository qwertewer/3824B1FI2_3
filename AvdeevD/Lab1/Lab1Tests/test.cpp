#include "pch.h"
#include "../Lab1/tbitfield.h"
#include "../Lab1/tset.h"

TEST(TBitFieldTestsGroup0, ConstructorValidSize) {
    TBitField bf(10);
    EXPECT_EQ(bf.GetLength(), 10);

    // Проверяем, что все биты установлены в 0
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(bf.GetBit(i), 0);
    }
}

TEST(TBitFieldTestsGroup0, ConstructorZeroSize) {
    EXPECT_NO_THROW(TBitField(0));
    TBitField field(0);
    EXPECT_EQ(field.GetLength(), 0);
}

TEST(TBitFieldTestsGroup0, ConstructorNegativeSize) {
    EXPECT_THROW(TBitField(-5), std::invalid_argument);
}

TEST(TBitFieldTestsGroup0, ConstructorLargeSize) {
    TBitField bf(1000);
    EXPECT_EQ(bf.GetLength(), 1000);

    // Проверяем крайние биты
    EXPECT_EQ(bf.GetBit(0), 0);
    EXPECT_EQ(bf.GetBit(999), 0);
}

// Тесты конструктора копирования
TEST(TBitFieldTestGroup1, CopyConstructor) {
    TBitField bf1(10);
    bf1.SetBit(3);
    bf1.SetBit(5);
    bf1.SetBit(7);

    TBitField bf2(bf1);
    EXPECT_EQ(bf2.GetLength(), 10);

    // Проверяем копирование битов
    EXPECT_EQ(bf2.GetBit(3), 1);
    EXPECT_EQ(bf2.GetBit(5), 1);
    EXPECT_EQ(bf2.GetBit(7), 1);
    EXPECT_EQ(bf2.GetBit(4), 0);

    // Проверяем, что это глубокое копирование
    bf2.SetBit(2);
    EXPECT_EQ(bf1.GetBit(2), 0); // Оригинал не должен измениться
}

// Тесты методов SetBit/GetBit/ClrBit
TEST(TBitFieldTestsGroup2, SetGetBitValid) {
    TBitField bf(10);

    bf.SetBit(0);
    EXPECT_EQ(bf.GetBit(0), 1);

    bf.SetBit(5);
    EXPECT_EQ(bf.GetBit(5), 1);

    bf.SetBit(9);
    EXPECT_EQ(bf.GetBit(9), 1);

    // Установка уже установленного бита
    bf.SetBit(5);
    EXPECT_EQ(bf.GetBit(5), 1);
}

TEST(TBitFieldTestsGroup2, SetBitOutOfRange) {
    TBitField bf(10);

    EXPECT_THROW(bf.SetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.SetBit(10), std::out_of_range);
    EXPECT_THROW(bf.SetBit(100), std::out_of_range);
}

TEST(TBitFieldTestsGroup2, GetBitOutOfRange) {
    TBitField bf(10);

    EXPECT_THROW(bf.GetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.GetBit(10), std::out_of_range);
    EXPECT_THROW(bf.GetBit(100), std::out_of_range);
}

TEST(TBitFieldTestsGroup2, ClrBitValid) {
    TBitField bf(10);

    bf.SetBit(5);
    EXPECT_EQ(bf.GetBit(5), 1);

    bf.ClrBit(5);
    EXPECT_EQ(bf.GetBit(5), 0);

    // Очистка уже очищенного бита
    bf.ClrBit(5);
    EXPECT_EQ(bf.GetBit(5), 0);

    // Очистка бита в начале и конце
    bf.SetBit(0);
    bf.SetBit(9);
    bf.ClrBit(0);
    bf.ClrBit(9);
    EXPECT_EQ(bf.GetBit(0), 0);
    EXPECT_EQ(bf.GetBit(9), 0);
}

TEST(TBitFieldTestsGroup2, ClrBitOutOfRange) {
    TBitField bf(10);

    EXPECT_THROW(bf.ClrBit(-1), std::out_of_range);
    EXPECT_THROW(bf.ClrBit(10), std::out_of_range);
}

// Тесты оператора присваивания
TEST(TBitFieldTestsGroup2, AssignmentOperator) {
    TBitField bf1(10);
    bf1.SetBit(2);
    bf1.SetBit(4);
    bf1.SetBit(6);

    TBitField bf2(5);
    bf2 = bf1;

    EXPECT_EQ(bf2.GetLength(), 10);
    EXPECT_EQ(bf2.GetBit(2), 1);
    EXPECT_EQ(bf2.GetBit(4), 1);
    EXPECT_EQ(bf2.GetBit(6), 1);
    EXPECT_EQ(bf2.GetBit(3), 0);

    // Проверка самоприсваивания
    bf2 = bf2;
    EXPECT_EQ(bf2.GetLength(), 10);
    EXPECT_EQ(bf2.GetBit(2), 1);
}

TEST(TBitFieldTestsGroup2, AssignmentDifferentSizes) {
    TBitField bf1(20);
    bf1.SetBit(10);
    bf1.SetBit(15);

    TBitField bf2(5);
    bf2 = bf1;

    EXPECT_EQ(bf2.GetLength(), 20);
    EXPECT_EQ(bf2.GetBit(10), 1);
    EXPECT_EQ(bf2.GetBit(15), 1);
    EXPECT_EQ(bf2.GetBit(5), 0);
}

// Тесты оператора сравнения
TEST(TBitFieldTestsGroup2, EqualityOperator) {
    TBitField bf1(10);
    bf1.SetBit(1);
    bf1.SetBit(3);
    bf1.SetBit(5);

    TBitField bf2(10);
    bf2.SetBit(1);
    bf2.SetBit(3);
    bf2.SetBit(5);

    TBitField bf3(10);
    bf3.SetBit(1);
    bf3.SetBit(4);

    TBitField bf4(15);
    bf4.SetBit(1);
    bf4.SetBit(3);
    bf4.SetBit(5);

    EXPECT_TRUE(bf1 == bf2);
    EXPECT_FALSE(bf1 == bf3);
    EXPECT_FALSE(bf1 == bf4);
}

TEST(TBitFieldTestsGroup2, InequalityOperator) {
    TBitField bf1(10);
    bf1.SetBit(1);
    bf1.SetBit(3);

    TBitField bf2(10);
    bf2.SetBit(1);
    bf2.SetBit(4);

    EXPECT_TRUE(bf1 != bf2);
    EXPECT_FALSE(bf1 != bf1);
}

// Тесты битовых операций
TEST(TBitFieldTestsGroup2, OrOperator) {
    TBitField bf1(10);
    bf1.SetBit(1);
    bf1.SetBit(3);
    bf1.SetBit(5);

    TBitField bf2(10);
    bf2.SetBit(2);
    bf2.SetBit(3);
    bf2.SetBit(6);

    TBitField result = (bf1 | bf2);

    EXPECT_EQ(result.GetLength(), 10);
    EXPECT_EQ(result.GetBit(1), 1);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(3), 1);
    EXPECT_EQ(result.GetBit(5), 1);
    EXPECT_EQ(result.GetBit(6), 1);
    EXPECT_EQ(result.GetBit(4), 0);
    EXPECT_EQ(result.GetBit(7), 0);
}

TEST(TBitFieldTestsGroup2, OrOperatorDifferentSizes) {
    TBitField bf1(5);
    bf1.SetBit(0);
    bf1.SetBit(2);

    TBitField bf2(10);
    bf2.SetBit(1);
    bf2.SetBit(3);
    bf2.SetBit(7);

    TBitField result = bf1 | bf2;

    EXPECT_EQ(result.GetLength(), 10);
    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(1), 1);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(3), 1);
    EXPECT_EQ(result.GetBit(7), 1);
    EXPECT_EQ(result.GetBit(4), 0);
}

TEST(TBitFieldTestsGroup2, AndOperator) {
    TBitField bf1(10);
    bf1.SetBit(1);
    bf1.SetBit(3);
    bf1.SetBit(5);
    bf1.SetBit(7);

    TBitField bf2(10);
    bf2.SetBit(3);
    bf2.SetBit(5);
    bf2.SetBit(6);
    bf2.SetBit(8);

    TBitField result = bf1 & bf2;

    EXPECT_EQ(result.GetLength(), 10);
    EXPECT_EQ(result.GetBit(3), 1);
    EXPECT_EQ(result.GetBit(5), 1);
    EXPECT_EQ(result.GetBit(1), 0);
    EXPECT_EQ(result.GetBit(6), 0);
    EXPECT_EQ(result.GetBit(7), 0);
    EXPECT_EQ(result.GetBit(8), 0);
}

TEST(TBitFieldTestsGroup2, AndOperatorDifferentSizes) {
    TBitField bf1(5);
    bf1.SetBit(0);
    bf1.SetBit(2);
    bf1.SetBit(4);

    TBitField bf2(10);
    bf2.SetBit(0);
    bf2.SetBit(2);
    bf2.SetBit(3);
    bf2.SetBit(7);

    TBitField result = bf1 & bf2;

    EXPECT_EQ(result.GetLength(), 10); // Минимальный размер
    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(4), 0); // В bf2 нет 4-го бита
    EXPECT_EQ(result.GetBit(3), 0); // В bf1 нет 3-го бита (выходит за пределы)
}

TEST(TBitFieldTestGroup2, NotOperator) {
    TBitField bf(8);
    bf.SetBit(0);
    bf.SetBit(2);
    bf.SetBit(5);

    TBitField result = ~bf;

    EXPECT_EQ(result.GetLength(), 8);
    EXPECT_EQ(result.GetBit(0), 0);
    EXPECT_EQ(result.GetBit(1), 1);
    EXPECT_EQ(result.GetBit(2), 0);
    EXPECT_EQ(result.GetBit(3), 1);
    EXPECT_EQ(result.GetBit(4), 1);
    EXPECT_EQ(result.GetBit(5), 0);
    EXPECT_EQ(result.GetBit(6), 1);
    EXPECT_EQ(result.GetBit(7), 1);
}

TEST(TBitFieldTestGroup2, NotOperatorLargeField) {
    const int SIZE = 100;
    TBitField bf(SIZE);

    // Устанавливаем все четные биты
    for (int i = 0; i < SIZE; i += 2) {
        bf.SetBit(i);
    }

    TBitField result = ~bf;

    // Проверяем, что инвертированы все биты
    for (int i = 0; i < SIZE; i++) {
        if (i % 2 == 0) {
            EXPECT_EQ(result.GetBit(i), 0);
        }
        else {
            EXPECT_EQ(result.GetBit(i), 1);
        }
    }
}

TEST(TBitFieldTestsGroup2, NotOperatorEdgeCase) {
    // Тестируем случай, когда размер не кратен размеру TELEM
    TBitField bf(10);

    // Устанавливаем все биты
    for (int i = 0; i < 10; i++) {
        bf.SetBit(i);
    }

    TBitField result = ~bf;

    // Все биты должны быть 0
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(result.GetBit(i), 0);
    }

    // Проверяем, что лишние биты в последнем элементе массива обнулены
    // (внутренняя проверка)
}

// Тесты потокового ввода/вывода
TEST(TBitFieldTestsGroup3, StreamOutput) {
    TBitField bf(8);
    bf.SetBit(0);
    bf.SetBit(2);
    bf.SetBit(5);
    bf.SetBit(7);

    std::stringstream ss;
    ss << bf;

    // Ожидаемый формат: 1 0 1 0 0 1 0 1
    // Но в реализации они выводятся без пробелов
    std::string expected = "10100101";
    std::string result = ss.str();

    // Удаляем пробелы из результата для сравнения
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    EXPECT_EQ(result, expected);
}

TEST(TBitFieldTestsGroup3, StreamInput) {
    TBitField bf(8);
    std::stringstream input("10100101");
    input >> bf;
    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(3), 0);
    EXPECT_EQ(bf.GetBit(4), 0);
    EXPECT_EQ(bf.GetBit(5), 1);
    EXPECT_EQ(bf.GetBit(6), 0);
    EXPECT_EQ(bf.GetBit(7), 1);
}

// Тесты краевых случаев

TEST(TBitFieldTestsEdge, MultipleOperations) {
    TBitField bf(20);

    // Серия операций
    bf.SetBit(5);
    bf.SetBit(10);
    bf.SetBit(15);

    EXPECT_EQ(bf.GetBit(5), 1);
    EXPECT_EQ(bf.GetBit(10), 1);
    EXPECT_EQ(bf.GetBit(15), 1);

    bf.ClrBit(10);
    EXPECT_EQ(bf.GetBit(10), 0);

    TBitField bf2 = ~bf;
    EXPECT_EQ(bf2.GetBit(5), 0);
    EXPECT_EQ(bf2.GetBit(10), 1);
    EXPECT_EQ(bf2.GetBit(15), 0);

    TBitField bf3 = bf | bf2;
    // Должен быть полный набор битов
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(bf3.GetBit(i), 1);
    }
}

TEST(TBitFieldTestsGroup4, MemoryUsage) {
    // Проверяем, что память используется эффективно
    // Размер TELEM обычно 4 байта (32 бита)

    TBitField bf1(32);  // Должен использовать 1 элемент
    TBitField bf2(33);  // Должен использовать 2 элемента
    TBitField bf3(64);  // Должен использовать 2 элемента
    TBitField bf4(65);  // Должен использовать 3 элемента

    // Основная проверка - корректность работы, а не точное использование памяти
    bf1.SetBit(31);
    EXPECT_EQ(bf1.GetBit(31), 1);

    bf2.SetBit(32);
    EXPECT_EQ(bf2.GetBit(32), 1);

    bf3.SetBit(63);
    EXPECT_EQ(bf3.GetBit(63), 1);

    bf4.SetBit(64);
    EXPECT_EQ(bf4.GetBit(64), 1);
}

// Тесты конструкторов
TEST(TSetTest, ConstructorValidSize) {
    TSet s(10);
    EXPECT_EQ(s.GetMaxPower(), 10);

    // Проверяем, что множество пустое
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(s.IsMember(i), 0);
    }
}

TEST(TSetTest, ConstructorZeroSize) {
    EXPECT_NO_THROW(TSet(0));
}

TEST(TSetTest, ConstructorNegativeSize) {
    EXPECT_THROW(TSet(-5), std::invalid_argument);
}

TEST(TSetTest, CopyConstructor) {
    TSet s1(10);
    s1.InsElem(2);
    s1.InsElem(5);
    s1.InsElem(8);

    TSet s2(s1);

    EXPECT_EQ(s2.GetMaxPower(), 10);
    EXPECT_EQ(s2.IsMember(2), 1);
    EXPECT_EQ(s2.IsMember(5), 1);
    EXPECT_EQ(s2.IsMember(8), 1);
    EXPECT_EQ(s2.IsMember(3), 0);

    // Проверка глубокого копирования
    s2.InsElem(4);
    EXPECT_EQ(s1.IsMember(4), 0);
}

TEST(TSetTest, ConstructorFromBitField) {
    TBitField bf(10);
    bf.SetBit(1);
    bf.SetBit(3);
    bf.SetBit(5);

    TSet s(bf);

    EXPECT_EQ(s.GetMaxPower(), 10);
    EXPECT_EQ(s.IsMember(1), 1);
    EXPECT_EQ(s.IsMember(3), 1);
    EXPECT_EQ(s.IsMember(5), 1);
    EXPECT_EQ(s.IsMember(2), 0);
}

TEST(TSetTest, ConversionToBitField) {
    TSet s(10);
    s.InsElem(2);
    s.InsElem(4);
    s.InsElem(6);

    TBitField bf = s; // Используем оператор преобразования

    EXPECT_EQ(bf.GetLength(), 10);
    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(4), 1);
    EXPECT_EQ(bf.GetBit(6), 1);
    EXPECT_EQ(bf.GetBit(3), 0);
}

// Тесты методов InsElem/DelElem/IsMember
TEST(TSetTest, InsElemValid) {
    TSet s(10);

    s.InsElem(0);
    EXPECT_EQ(s.IsMember(0), 1);

    s.InsElem(5);
    EXPECT_EQ(s.IsMember(5), 1);

    s.InsElem(9);
    EXPECT_EQ(s.IsMember(9), 1);

    // Добавление уже существующего элемента
    s.InsElem(5);
    EXPECT_EQ(s.IsMember(5), 1);
}

TEST(TSetTest, InsElemOutOfRange) {
    TSet s(10);

    EXPECT_THROW(s.InsElem(-1), std::out_of_range);
    EXPECT_THROW(s.InsElem(10), std::out_of_range);
    EXPECT_THROW(s.InsElem(100), std::out_of_range);
}

TEST(TSetTest, DelElemValid) {
    TSet s(10);

    s.InsElem(5);
    EXPECT_EQ(s.IsMember(5), 1);

    s.DelElem(5);
    EXPECT_EQ(s.IsMember(5), 0);

    // Удаление несуществующего элемента
    s.DelElem(5);
    EXPECT_EQ(s.IsMember(5), 0);

    // Удаление элементов на границах
    s.InsElem(0);
    s.InsElem(9);
    s.DelElem(0);
    s.DelElem(9);
    EXPECT_EQ(s.IsMember(0), 0);
    EXPECT_EQ(s.IsMember(9), 0);
}

TEST(TSetTest, DelElemOutOfRange) {
    TSet s(10);

    EXPECT_THROW(s.DelElem(-1), std::out_of_range);
    EXPECT_THROW(s.DelElem(10), std::out_of_range);
}

TEST(TSetTest, IsMemberOutOfRange) {
    TSet s(10);

    EXPECT_THROW(s.IsMember(-1), std::out_of_range);
    EXPECT_THROW(s.IsMember(10), std::out_of_range);
}

// Тесты операторов сравнения
TEST(TSetTest, EqualityOperator) {
    TSet s1(10);
    s1.InsElem(1);
    s1.InsElem(3);
    s1.InsElem(5);

    TSet s2(10);
    s2.InsElem(1);
    s2.InsElem(3);
    s2.InsElem(5);

    TSet s3(10);
    s3.InsElem(1);
    s3.InsElem(4);

    TSet s4(15);
    s4.InsElem(1);
    s4.InsElem(3);
    s4.InsElem(5);

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_FALSE(s1 == s4);
}

TEST(TSetTest, InequalityOperator) {
    TSet s1(10);
    s1.InsElem(1);
    s1.InsElem(3);

    TSet s2(10);
    s2.InsElem(1);
    s2.InsElem(4);

    EXPECT_TRUE(s1 != s2);
    EXPECT_FALSE(s1 != s1);
}

// Тесты оператора присваивания
TEST(TSetTest, AssignmentOperator) {
    TSet s1(10);
    s1.InsElem(2);
    s1.InsElem(4);
    s1.InsElem(6);

    TSet s2(5);
    s2 = s1;

    EXPECT_EQ(s2.GetMaxPower(), 10);
    EXPECT_EQ(s2.IsMember(2), 1);
    EXPECT_EQ(s2.IsMember(4), 1);
    EXPECT_EQ(s2.IsMember(6), 1);
    EXPECT_EQ(s2.IsMember(3), 0);

    // Проверка самоприсваивания
    s2 = s2;
    EXPECT_EQ(s2.GetMaxPower(), 10);
    EXPECT_EQ(s2.IsMember(2), 1);
}

// Тесты теоретико-множественных операций
TEST(TSetTest, UnionWithElement) {
    TSet s(10);
    s.InsElem(2);
    s.InsElem(4);

    TSet result = s + 6;

    EXPECT_EQ(result.GetMaxPower(), 10);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(4), 1);
    EXPECT_EQ(result.IsMember(6), 1);
    EXPECT_EQ(result.IsMember(3), 0);
}

TEST(TSetTest, UnionWithElementOutOfRange) {
    TSet s(10);
    EXPECT_THROW(s + (-1), std::out_of_range);
    EXPECT_THROW(s + 10, std::out_of_range);
}

TEST(TSetTest, DifferenceWithElement) {
    TSet s(10);
    s.InsElem(2);
    s.InsElem(4);
    s.InsElem(6);

    TSet result = s - 4;

    EXPECT_EQ(result.GetMaxPower(), 10);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(4), 0);
    EXPECT_EQ(result.IsMember(6), 1);
}

TEST(TSetTest, DifferenceWithElementOutOfRange) {
    TSet s(10);
    EXPECT_THROW(s - (-1), std::out_of_range);
    EXPECT_THROW(s - 10, std::out_of_range);
}

TEST(TSetTest, UnionOfSets) {
    TSet s1(10);
    s1.InsElem(1);
    s1.InsElem(3);
    s1.InsElem(5);

    TSet s2(10);
    s2.InsElem(2);
    s2.InsElem(3);
    s2.InsElem(6);

    TSet result = s1 + s2;

    EXPECT_EQ(result.GetMaxPower(), 10);
    EXPECT_EQ(result.IsMember(1), 1);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(3), 1);
    EXPECT_EQ(result.IsMember(5), 1);
    EXPECT_EQ(result.IsMember(6), 1);
    EXPECT_EQ(result.IsMember(4), 0);
    EXPECT_EQ(result.IsMember(7), 0);
}

TEST(TSetTest, UnionOfSetsDifferentSizes) {
    TSet s1(5);

    TSet s2(10);

    EXPECT_THROW(TSet result = s1 + s2, std::invalid_argument);
}

TEST(TSetTest, IntersectionOfSets) {
    TSet s1(10);
    s1.InsElem(1);
    s1.InsElem(3);
    s1.InsElem(5);
    s1.InsElem(7);

    TSet s2(10);
    s2.InsElem(3);
    s2.InsElem(5);
    s2.InsElem(6);
    s2.InsElem(8);

    TSet result = s1 * s2;

    EXPECT_EQ(result.GetMaxPower(), 10);
    EXPECT_EQ(result.IsMember(3), 1);
    EXPECT_EQ(result.IsMember(5), 1);
    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(6), 0);
    EXPECT_EQ(result.IsMember(7), 0);
    EXPECT_EQ(result.IsMember(8), 0);
}

TEST(TSetTest, IntersectionOfSetsDifferentSizes) {
    TSet s1(5);

    TSet s2(10);

    EXPECT_THROW(TSet Inters(s1 * s2), std::invalid_argument);
    
}

TEST(TSetTest, Complement) {
    TSet s(8);
    s.InsElem(0);
    s.InsElem(2);
    s.InsElem(5);

    TSet result = ~s;

    EXPECT_EQ(result.GetMaxPower(), 8);
    EXPECT_EQ(result.IsMember(0), 0);
    EXPECT_EQ(result.IsMember(1), 1);
    EXPECT_EQ(result.IsMember(2), 0);
    EXPECT_EQ(result.IsMember(3), 1);
    EXPECT_EQ(result.IsMember(4), 1);
    EXPECT_EQ(result.IsMember(5), 0);
    EXPECT_EQ(result.IsMember(6), 1);
    EXPECT_EQ(result.IsMember(7), 1);
}

TEST(TSetTest, ComplementFullSet) {
    TSet s(10);
    for (int i = 0; i < 10; i++) {
        s.InsElem(i);
    }

    TSet result = ~s;

    // Дополнение полного множества - пустое множество
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(result.IsMember(i), 0);
    }
}

TEST(TSetTest, ComplementEmptySet) {
    TSet s(10);

    TSet result = ~s;

    // Дополнение пустого множества - полное множество
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(result.IsMember(i), 1);
    }
}

// Тесты потокового ввода/вывода
TEST(TSetTest, StreamOutput) {
    TSet s(10);
    s.InsElem(2);
    s.InsElem(5);
    s.InsElem(8);

    std::stringstream ss;
    ss << s;

    // Ожидаемый формат: { 2, 5, 8 }
    std::string result = ss.str();

    // Проверяем наличие элементов
    EXPECT_TRUE(result.find('2') != std::string::npos);
    EXPECT_TRUE(result.find('5') != std::string::npos);
    EXPECT_TRUE(result.find('8') != std::string::npos);
    EXPECT_TRUE(result.find('{') != std::string::npos);
    EXPECT_TRUE(result.find('}') != std::string::npos);
}

TEST(TSetTest, StreamInput) {
    TSet s(10);
    std::stringstream ss("2 5 8 -1"); // -1 как признак конца

    ss >> s;

    EXPECT_EQ(s.IsMember(2), 1);
    EXPECT_EQ(s.IsMember(5), 1);
    EXPECT_EQ(s.IsMember(8), 1);
    EXPECT_EQ(s.IsMember(3), 0);
}

// Тесты краевых случаев
TEST(TSetTest, BoundaryElements) {
    TSet s(100);

    // Добавляем элементы на границах
    s.InsElem(0);
    s.InsElem(99);

    EXPECT_EQ(s.IsMember(0), 1);
    EXPECT_EQ(s.IsMember(99), 1);
    EXPECT_EQ(s.IsMember(50), 0);

    s.DelElem(0);
    s.DelElem(99);

    EXPECT_EQ(s.IsMember(0), 0);
    EXPECT_EQ(s.IsMember(99), 0);
}

TEST(TSetTest, MultipleOperations) {
    TSet s(20);

    // Серия операций
    s.InsElem(5);
    s.InsElem(10);
    s.InsElem(15);

    EXPECT_EQ(s.IsMember(5), 1);
    EXPECT_EQ(s.IsMember(10), 1);
    EXPECT_EQ(s.IsMember(15), 1);

    s.DelElem(10);
    EXPECT_EQ(s.IsMember(10), 0);

    TSet s2 = ~s;
    EXPECT_EQ(s2.IsMember(5), 0);
    EXPECT_EQ(s2.IsMember(10), 1);
    EXPECT_EQ(s2.IsMember(15), 0);

    TSet s3 = s + s2;
    // Должно быть полное множество
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(s3.IsMember(i), 1);
    }

    TSet s4 = s * s2;
    // Пересечение должно быть пустым
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(s4.IsMember(i), 0);
    }
}

TEST(TSetTest, SetProperties) {
    // Проверка свойств множеств
    TSet A(10);
    A.InsElem(1);
    A.InsElem(3);
    A.InsElem(5);

    TSet B(10);
    B.InsElem(3);
    B.InsElem(5);
    B.InsElem(7);

    // Коммутативность объединения
    TSet C1 = A + B;
    TSet C2 = B + A;
    EXPECT_TRUE(C1 == C2);

    // Коммутативность пересечения
    TSet D1 = A * B;
    TSet D2 = B * A;
    EXPECT_TRUE(D1 == D2);

    // Идемпотентность
    TSet E1 = A + A;
    EXPECT_TRUE(E1 == A);

    TSet F1 = A * A;
    EXPECT_TRUE(F1 == A);

    // Закон де Моргана: ~(A + B) == ~A * ~B
    TSet G1 = ~(A + B);
    TSet G2 = (~A) * (~B);
    EXPECT_TRUE(G1 == G2);

    // Закон де Моргана: ~(A * B) == ~A + ~B
    TSet H1 = ~(A * B);
    TSet H2 = (~A) + (~B);
    EXPECT_TRUE(H1 == H2);
}

TEST(TSetTest, LargeSetOperations) {
    const int SIZE = 1000;
    TSet s1(SIZE);
    TSet s2(SIZE);

    // Заполняем множества
    for (int i = 0; i < SIZE; i++) {
        if (i % 2 == 0) {
            s1.InsElem(i);
        }
        if (i % 3 == 0) {
            s2.InsElem(i);
        }
    }

    // Объединение
    TSet unionSet = s1 + s2;
    for (int i = 0; i < SIZE; i++) {
        bool expected = (i % 2 == 0) || (i % 3 == 0);
        EXPECT_EQ(unionSet.IsMember(i), expected ? 1 : 0);
    }

    // Пересечение
    TSet intersectionSet = s1 * s2;
    for (int i = 0; i < SIZE; i++) {
        bool expected = (i % 2 == 0) && (i % 3 == 0); // i % 6 == 0
        EXPECT_EQ(intersectionSet.IsMember(i), expected ? 1 : 0);
    }

    // Дополнение
    TSet complementSet = ~s1;
    for (int i = 0; i < SIZE; i++) {
        bool expected = (i % 2 != 0);
        EXPECT_EQ(complementSet.IsMember(i), expected ? 1 : 0);
    }
}