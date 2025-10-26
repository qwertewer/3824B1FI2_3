#include "pch.h"
#include "../Project1/tbitfield.h"
#include "../Project1/tset.h"

//////
TEST(Test_TBitField0, Constructor_zero_lenght) {
    TBitField field(0);
    EXPECT_EQ(field.GetLength(), 0);

}

TEST(Test_TBitField0, Constructor_positive_length) {
    TBitField field(10);
    EXPECT_EQ(field.GetLength(), 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(field.GetBit(i), 0); //все биты имеют нулевое значение
    }
}

TEST(Test_TBitField0, Constructor_negative_length) {
    try {
        TBitField field(-1);
        FAIL();
    }
    catch (const std::invalid_argument& a) {
        SUCCEED();
        EXPECT_STREQ(a.what(), "Error! The length is less than zero"); //сообщение об ошибке совпадает
    }
}
////////

////////конструктор копирования
TEST(Test_TBitField0, Constructor_copy) {
    TBitField field_original(5);
    for (size_t i = 0; i < field_original.GetLength(); ++i) {
        field_original.SetBit(i);
    }

    TBitField field_copy(field_original);
    EXPECT_EQ(field_original.GetLength(), field_copy.GetLength()); //равенство длин

    for (size_t i = 0; i < field_original.GetLength(); ++i) {
        EXPECT_EQ(field_original.GetBit(i), field_copy.GetBit(i));
    }

}

TEST(Test_TBitField0, Constructor_copy_2) {
    TBitField field_original(5);
    for (size_t i = 0; i < field_original.GetLength(); ++i) {
        field_original.SetBit(i);
    }

    TBitField field_copy(field_original);
    field_original.ClrBit(0);

    EXPECT_NE(field_original.GetBit(0), field_copy.GetBit(0)); //изменение бита в original не привело к изменению бита в copy
    EXPECT_TRUE(field_copy.GetBit(0));

}

TEST(Test_TBitField0, Constructor_copy_3) { //копирование пустого объекта
    TBitField field_original(0);
    TBitField field_copy(field_original);
    EXPECT_EQ(field_original.GetLength(), field_copy.GetLength());
}

TEST(Test_TBitField0, Constructor_copy_4) { //большой объем данных
    TBitField field_original(1000);
    for (size_t i = 0; i < field_original.GetLength(); ++i) {
        field_original.SetBit(i);
    }

    TBitField field_copy(field_original);
    EXPECT_EQ(field_original.GetLength(), field_copy.GetLength()); //равенство длин

    for (size_t i = 0; i < field_original.GetLength(); ++i) {
        EXPECT_EQ(field_original.GetBit(i), field_copy.GetBit(i));
    }
}
/////////

TEST(Test_TBitField1, Get_lenght) {
    TBitField field(15);
    int len = field.GetLength();
    EXPECT_EQ(len, 15);
}
////////
TEST(Test_TBitField1, Set_bit) {
    TBitField field(5);
    field.SetBit(0);
    field.SetBit(4);
    EXPECT_EQ(field.GetBit(0), 1); //бит, к которому применили метод стал 1 
    EXPECT_EQ(field.GetBit(1), 0); //бит, к которому не применяли метод остался 0 
    EXPECT_EQ(field.GetBit(2), 0);
    EXPECT_EQ(field.GetBit(3), 0);
    int a = field.GetBit(4);
    EXPECT_EQ(field.GetBit(4), 1);
}

TEST(Test_TBitField1, Set_bit_2) {
    TBitField field(5);
    try {
        field.SetBit(-1); //индекс меньше 0
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Set_bit_2_1) {
    TBitField field(5);
    try {
        field.SetBit(5); //индекс равен длине
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Set_bit_2_2) {
    TBitField field(5);
    try {
        field.SetBit(6); //индекс больше длины
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Set_bit_3) {
    TBitField field(0);
    try {
        field.SetBit(0);
        FAIL();
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The length of the bit field is 0. No memory allocated for objects");
        SUCCEED();
    }
}
////////////
TEST(Test_TBitField1, Glr_bit) {
    TBitField field(3);
    field.SetBit(0);
    field.ClrBit(0);
    EXPECT_EQ(field.GetBit(0), 0);
    EXPECT_EQ(field.GetBit(1), 0);
}

TEST(Test_TBitField1, Glr_bit_2_1) {
    TBitField field(3);
    try {
        field.ClrBit(-1);
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Glr_bit_2_2) {
    TBitField field(3);
    try {
        field.ClrBit(3);
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Glr_bit_2_3) {
    TBitField field(3);
    try {
        field.ClrBit(4);
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Glr_bit_3) {
    TBitField field(0);
    try {
        field.ClrBit(0);
        FAIL();
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The length of the bit field is 0. No memory allocated for objects");
        SUCCEED();
    }
}
////////////
TEST(Test_TBitField1, Get_Bit) {
    TBitField field(3);
    field.SetBit(1);
    int k = field.GetBit(0);
    int k1 = field.GetBit(1);
    EXPECT_EQ(k, 0);
    EXPECT_EQ(k1, 1);

}

TEST(Test_TBitField1, Get_Bit_2) {
    TBitField field(3);

    try {
        field.GetBit(-1);
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Get_Bit_2_1) {
    TBitField field(3);

    try {
        field.GetBit(3);
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Get_Bit_2_2) {
    TBitField field(3);

    try {
        field.GetBit(4);
        FAIL();
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Error! Incorrect bit index");
        SUCCEED();
    }
}

TEST(Test_TBitField1, Get_Bit_3) {
    TBitField field(0);

    try {
        field.GetBit(-1);
        FAIL();
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The length of the bit field is 0. No memory allocated for objects");
        SUCCEED();
    }
}
/////////

////битовые операции
TEST(Test_TBitField2, Oper_eq) {
    TBitField field1(5);
    TBitField field2(5);
    field1.SetBit(1);
    field2.SetBit(1);
    EXPECT_TRUE(field1 == field2);
}

TEST(Test_TBitField2, Oper_eq_1) {
    TBitField field1(0);
    TBitField field2(0);
    EXPECT_TRUE(field1 == field2);
}

TEST(Test_TBitField2, Oper_eq_2) {
    TBitField field1(5);
    TBitField field2(4); //длины не свопадают
    EXPECT_FALSE(field1 == field2);
}

TEST(Test_TBitField2, Oper_eq_2_1) {
    TBitField field1(5);
    TBitField field2(5);
    field1.SetBit(1); //изменяем бит в поле номер 1. Во втором ничего не меняем

    EXPECT_FALSE(field1 == field2);
}

TEST(Test_TBitField2, Oper_eq_2_2) {
    TBitField field1(5);
    TBitField field2(0);
    EXPECT_FALSE(field1 == field2);
}
////////
TEST(Test_TBitField2, Oper_not_eq) { //разная длина битовых полей
    TBitField field1(2);
    TBitField field2(1);
    EXPECT_TRUE(field1 != field2);
}

TEST(Test_TBitField2, Oper_not_eq_1) { //изменение значения бита
    TBitField field1(2);
    TBitField field2(2);
    field1.SetBit(1);
    EXPECT_TRUE(field1 != field2);
}

TEST(Test_TBitField2, Oper_not_eq_2) { //длины равны 0
    TBitField field1(0);
    TBitField field2(0);

    EXPECT_FALSE(field1 != field2);
}
/////////
//оператор присваивания
TEST(Test_TBitField2, Oper_assign) {
    TBitField field(3);
    field.SetBit(1);
    TBitField field2(1);
    field2 = field;
    EXPECT_EQ(field2.GetLength(), 3);
    for (int i = 0; i < field.GetLength(); ++i) {
        EXPECT_EQ(field2.GetBit(i), field.GetBit(i));
    }
}

TEST(Test_TBitField2, Oper_assign_1) { //присвоение полю самого себя
    TBitField field(3);

    field = field;
    EXPECT_EQ(field.GetLength(), 3);
    for (int i = 0; i < field.GetLength(); ++i) {
        EXPECT_EQ(field.GetBit(i), field.GetBit(i));
    }
}

TEST(Test_TBitField2, Oper_assign_2) { //присвоение поля длины 0
    TBitField field(0);
    TBitField field2(3);
    field2 = field;
    EXPECT_EQ(field.GetLength(), 0);
}

TEST(Test_TBitField2, Oper_assign_3) { //несколько присвоений подряд
    TBitField field(3);
    TBitField field2(2);
    TBitField field3(1);

    field.SetBit(2);

    field3 = field2 = field;

    EXPECT_EQ(field3.GetLength(), 3);


    for (int i = 0; i < field.GetLength(); ++i) {
        EXPECT_EQ(field3.GetBit(i), field.GetBit(i));
    }
}
///////////
///////////
TEST(Test_TBitField2, Oper_OR) {
    TBitField field(3);
    TBitField field2(3);
    field.SetBit(2);
    TBitField field3 = field | field2; //field: 001, field2: 000
    EXPECT_EQ(field3.GetLength(), 3);
    EXPECT_EQ(field3.GetBit(2), 1); //field3: 001
}

TEST(Test_TBitField2, Oper_OR_1) {
    TBitField field(3);
    TBitField field2(2); //размеры полей разные
    field2.SetBit(0);
    field2.SetBit(1);
    TBitField field3 = field | field2; //field: 000, field2: 011
    EXPECT_EQ(field3.GetLength(), 3);
    EXPECT_EQ(field3.GetBit(0), 1); //field3: 011
    EXPECT_EQ(field3.GetBit(1), 1);
}

TEST(Test_TBitField2, Oper_OR_1_1) {
    TBitField field(35);
    TBitField field2(2);
    field.SetBit(0);
    field.SetBit(34);

    field2.SetBit(0);
    field2.SetBit(1);
    TBitField field3 = field | field2;
    for (size_t i = 2; i < field3.GetLength()-1; ++i) {
        EXPECT_EQ(field3.GetBit(i), 0);
    }
    EXPECT_EQ(field3.GetBit(0), 1); 
    EXPECT_EQ(field3.GetBit(1), 1); 
    EXPECT_EQ(field3.GetBit(34), 1); 
}

TEST(Test_TBitField2, Oper_OR_2) {
    TBitField field(0); //размер одного объекта равен 0
    TBitField field2(2);
    field2.SetBit(0);
    field2.SetBit(1);
    TBitField field3 = field | field2; //field: -, field2: 011
    EXPECT_EQ(field3.GetLength(), 2);
    EXPECT_EQ(field3.GetBit(0), 1); //field3: 011
    EXPECT_EQ(field3.GetBit(1), 1);
}

TEST(Test_TBitField2, Oper_OR_3) {
    TBitField field(0); //оба обекта имеют длину 0
    TBitField field2(0);

    TBitField field3 = field | field2; 
    EXPECT_EQ(field3.GetLength(), 0);
}
////////////

TEST(Test_TBitField2, Oper_AND) {
    TBitField field(3); //длины полей имеют одинаковую дину
    TBitField field2(3);
    field.SetBit(1);
    field2.SetBit(0);
    field2.SetBit(1);
    TBitField field3 = field & field2; //field:010, field2: 011
    EXPECT_EQ(field3.GetLength(), 3);
    EXPECT_EQ(field3.GetBit(0), 0);
    EXPECT_EQ(field3.GetBit(1), 1); //field3: 010
}

TEST(Test_TBitField2, Oper_AND_1) {
    TBitField field(3); //разная длина полей
    TBitField field2(2);
    field.SetBit(0);
    field.SetBit(1);

    field2.SetBit(0);
    field2.SetBit(1);

    TBitField field3 = field & field2; //field: 011, field2: 11
    EXPECT_EQ(field3.GetLength(), 3);
    EXPECT_EQ(field3.GetBit(0), 1);
    EXPECT_EQ(field3.GetBit(1), 1); //field3: 11 
}

TEST(Test_TBitField2, Oper_AND_1_1) {
    TBitField field(2); //разная длина полей
    TBitField field2(3);
    field.SetBit(0);
    
    field2.SetBit(0);
    field2.SetBit(2);

    TBitField field3 = field & field2; //field: 01, field2: 101
    EXPECT_EQ(field3.GetLength(), 3);
    EXPECT_EQ(field3.GetBit(0), 1);
    EXPECT_EQ(field3.GetBit(1), 0); //field3: 011 
    EXPECT_EQ(field3.GetBit(2), 0);
}

TEST(Test_TBitField2, Oper_AND_1_2) {
    TBitField field(35);
    TBitField field2(2);
    field.SetBit(0);
    field.SetBit(34);

    field2.SetBit(0);
    TBitField field3 = field & field2; 
    EXPECT_EQ(field3.GetLength(), 35);
    for (size_t i = 1; i < field3.GetLength()-1; ++i) {
        EXPECT_EQ(field3.GetBit(i), 0);
    }
    EXPECT_EQ(field3.GetBit(0), 1);
    EXPECT_EQ(field3.GetBit(34), 0);
}


TEST(Test_TBitField2, Oper_AND_2) {
    TBitField field(0); //длина одного из полей равна 0
    TBitField field2(2);
    field2.SetBit(0);
    TBitField field3 = field & field2;
    EXPECT_EQ(field3.GetLength(), 2);
    EXPECT_EQ(field3.GetBit(0), 1);
    EXPECT_EQ(field3.GetBit(1), 0);
}

TEST(Test_TBitField2, Oper_AND_3) {
    TBitField field(0); //длины каждого поля равны 0
    TBitField field2(0);

    TBitField field3 = field & field2;
    EXPECT_EQ(field3.GetLength(), 0);
}
///////////
TEST(Test_TBitField2, Oper_denial) {
    TBitField field(3);
    field.SetBit(0);
    field.SetBit(2);
    TBitField field2 = ~field;

    ASSERT_EQ(field2.GetBit(0), 0);
    ASSERT_EQ(field2.GetBit(1), 1);
    ASSERT_EQ(field2.GetBit(2), 0);

}


TEST(Test_TBitField2, Oper_denial_1) {
    TBitField field(34);

    field.SetBit(33);
    field.SetBit(32);

    TBitField field2 = ~field;
    EXPECT_EQ(field2.GetBit(33), 0);
    EXPECT_EQ(field2.GetBit(32), 0);

    for (size_t i = 0; i < field2.GetLength() - 2; ++i) {
        ASSERT_EQ(field2.GetBit(i), 1);
    }
}

TEST(Test_TBitField2, Oper_denial_2) {
    TBitField field(0);
    try {
        TBitField field2 = ~field;
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "Error! The field length is 0");
    }
}
/////////////
//поток ввода
TEST(Test_TBitField3, Oper_input) {
    TBitField field(3);
    std::istringstream in("110");
    in >> field;

    ASSERT_EQ(field.GetBit(0), 0);
    ASSERT_EQ(field.GetBit(1), 1);
    ASSERT_EQ(field.GetBit(2), 1);
}

TEST(Test_TBitField3, Oper_input_1) {
    TBitField field(3);
    std::istringstream in("01");
    try {
        in >> field;
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "Error!! Incorrect length");
    }
}


TEST(Test_TBitField3, Oper_input_2) {
    TBitField field(3);
    std::istringstream in("1a1");
    try {
        in >> field;
    }
    catch (const std::invalid_argument& a) {
        EXPECT_STREQ(a.what(), "Incorrect symbol");
    }
}

TEST(Test_TBitField3, Oper_input_3) { 
    TBitField field1(3);
    TBitField field2(3);

    std::istringstream in("110 011");

    in >> field1 >> field2;

    ASSERT_EQ(field1.GetBit(0), 0);
    ASSERT_EQ(field1.GetBit(1), 1);
    ASSERT_EQ(field1.GetBit(2), 1);

    ASSERT_EQ(field2.GetBit(0), 1);
    ASSERT_EQ(field2.GetBit(1), 1);
    ASSERT_EQ(field2.GetBit(2), 0);
}
////////////
////поток вывода
TEST(Test_TBitField3, Oper_output) {
    TBitField field(3);
    field.SetBit(2);
    field.SetBit(1);
    std::ostringstream out;
    out << field;

    EXPECT_EQ(out.str(), "110");
}

TEST(Test_TBitField3, Oper_output_2) {
    TBitField field(0);
    try {
        std::ostringstream out;
        out << field;
        FAIL();
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The field length is 0");
        SUCCEED();
    }
}

TEST(Test_TBitField3, Oper_output_3) {
    TBitField field(3);
    field.SetBit(2);
    field.SetBit(1); //field: 110

    TBitField field2(3);
    field2.SetBit(0); //field2: 001

    std::ostringstream out;
    out << field << " " << field2;
    EXPECT_EQ(out.str(), "110 001");
}
///////////

///////////
TEST(Test_Tset0, Constructor) {
    TSet set(3);
} 
TEST(Test_Tset0, Constructor_1) {
    try {
        TSet set(-1);
    }
    catch (const std::invalid_argument& a) {
        EXPECT_STREQ(a.what(), "Error! The length is less than zero");
    }
}
/////////////
TEST(Test_Tset0, Constructor_copy) {
    TSet set1(5);
    set1.InsElem(0);
    TSet set2(set1);
    EXPECT_TRUE(set2 == set1);
}
///////////
TEST(Test_Tset0, Constructor_transform) {
    TBitField field(4);
    field.SetBit(0);
    field.SetBit(1);

    TSet set(field);
    EXPECT_EQ(set.GetMaxPower(), 4); //проверили мощность

    //проверим битовое поле
    TBitField field2 = static_cast<TBitField>(set);
    EXPECT_TRUE(field2 == field);

}

////////////
TEST(Test_Tset0, Costructor_transform_field) {
    TSet set(4);
    TBitField field = static_cast<TBitField>(set);
    EXPECT_EQ(field.GetLength(), 4);
}
////////////
TEST(Test_Tset1, MaxPower) {
    TSet set(10);
    EXPECT_EQ(set.GetMaxPower(), 10);

}
///////////
TEST(Test_Tset1, InsElem) {
    TSet set(4);
    set.InsElem(0);
    set.InsElem(3);

    TBitField field = static_cast<TBitField>(set);

    EXPECT_EQ(field.GetBit(0), 1);
    EXPECT_EQ(field.GetBit(3), 1);
}

TEST(Test_Tset1, InsElem_1) {
    TSet set(0);
    try {
        set.InsElem(0);
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The power of the set is 0");
    }
}

TEST(Test_Tset1, InsElem_2) {
    TSet set(3);
    try {
        set.InsElem(4);
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Elem < 0 or elem >= power of set");
    }
}
////////////
TEST(Test_Tset1, Del_elem) {
    TSet set(3);
    set.InsElem(1);
    set.DelElem(1);

    TBitField field = static_cast<TBitField>(set);
    EXPECT_EQ(field.GetBit(1), 0);
}

TEST(Test_Tset1, Del_elem_1) {
    TSet set(3);

    try {
        set.DelElem(-1);
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Elem < 0 or elem >= power of set");

    }
}
////////////
TEST(Test_Tset1, Is_Member) {
    TSet set(3);
    set.InsElem(1);
    EXPECT_EQ(set.IsMember(1), 1);
    EXPECT_EQ(set.IsMember(2), 0);
}
///////////
TEST(Test_Tset2, Oper_eq) {
    TSet set(4);
    set.InsElem(0);

    TSet set2(4);
    set2.InsElem(0);

    EXPECT_TRUE(set == set2);
}

TEST(Test_Tset2, Oper_eq_1) {
    TSet set(4);
    set.InsElem(0);

    TSet set2(4);
    set2.InsElem(1);

    EXPECT_FALSE(set == set2);
}
////////
TEST(Test_Tset2, Oper_not_eq) {
    TSet set(4);
    set.InsElem(0);

    TSet set2(4);
    set2.InsElem(1);

    EXPECT_TRUE(set != set2);
}

TEST(Test_Tset2, Oper_not_eq_1) {
    TSet set(4);
    set.InsElem(0);

    TSet set2(4);
    set2.InsElem(0);

    EXPECT_FALSE(set != set2);
}
/////////
TEST(Test_Tset2, Oper_equality) {
    TSet set(4);
    set.InsElem(2);

    TSet set2(1);
    set2 = set;

    EXPECT_TRUE(set2 == set);
}

TEST(Test_Tset2, Oper_equality_1) {
    TSet set(4);
    set.InsElem(2);

    set = set;
    EXPECT_TRUE(set == set);
}

TEST(Test_Tset2, Oper_equality_2) {
    TSet set(4);
    set.InsElem(2);

    TSet set2(1);
    set2 = set;

    TSet set3(0);

    set3 = set2 = set;
    EXPECT_TRUE(set2 == set);
    EXPECT_TRUE(set3 == set);
}
///////////
TEST(Test_Tset2, Oper_join) {
    TSet set(4);
    set = set + 1; //добавили элемент с индексом 1
    EXPECT_EQ(set.IsMember(1), 1);
}

TEST(Test_Tset2, Oper_join_1) {
    TSet set(4);
    try {
        set = set + (-1);
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Elem < 0 or elem >= power of set");
    }
}

TEST(Test_Tset2, Oper_join_2) {
    TSet set(0);
    try {
        set = set + 2;
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The maximum power of the set is 0. There are no elements that can be added");
    }
}
////////////
TEST(Test_Tset2, Oper_difference) {
    TSet set(4);
    set.InsElem(3);
    set = set - 3;
    EXPECT_EQ(set.IsMember(3), 0);
}
TEST(Test_Tset2, Oper_difference_1) {
    TSet set(4);
    try {
        set = set - 5;
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Elem < 0 or elem >= power of set");
    }
}
///////////
TEST(Test_Tset3, Oper_addition) {
    TSet set(4);
    set.InsElem(0);
    set.InsElem(3); //1001

    TSet set2 = ~set;
    EXPECT_EQ(set2.IsMember(0), 0);
    EXPECT_EQ(set2.IsMember(1), 1);
    EXPECT_EQ(set2.IsMember(2), 1);
    EXPECT_EQ(set2.IsMember(3), 0); //0110
}


TEST(Test_Tset3, Oper_addition_1) {
    TSet set(5);
    set.InsElem(0);
    set.InsElem(1); //11000

    set = ~set;
    EXPECT_EQ(set.IsMember(0), 0);
    EXPECT_EQ(set.IsMember(1), 0);
    EXPECT_EQ(set.IsMember(2), 1);
    EXPECT_EQ(set.IsMember(3), 1);
    EXPECT_EQ(set.IsMember(4), 1);
}

TEST(Test_Tset3, Oper_addition_2) {
    TSet set(34);
    set.InsElem(33);
    set.InsElem(32);

    set = ~set;
    EXPECT_EQ(set.IsMember(33), 0);
    EXPECT_EQ(set.IsMember(32), 0);
    for (size_t i = 0; i < set.GetMaxPower() - 2; ++i) {
        EXPECT_EQ(set.IsMember(i), 1);
    }
}
////////////

TEST(Test_Tset3, Oper_unification) {

    TSet set(3);
    set.InsElem(0);

    TSet set2(3);
    set2.InsElem(1);

    TSet set3 = set + set2;
    EXPECT_EQ(set3.IsMember(0), 1);
    EXPECT_EQ(set3.IsMember(1), 1);
    EXPECT_EQ(set3.IsMember(2), 0);
}

TEST(Test_Tset3, Oper_unification_1) { 

    TSet set(0);

    TSet set2(0);

    TSet set3 = set + set2;

    EXPECT_EQ(set3.GetMaxPower(), 0);
}

TEST(Test_Tset3, Oper_unification_2) { 
    TSet set(3);
    set.InsElem(0);

    TSet set2 = set + set;
    EXPECT_EQ(set2.IsMember(0), 1);
    EXPECT_EQ(set2.IsMember(1), 0);
    EXPECT_EQ(set2.IsMember(2), 0);
}

TEST(Test_Tset3, Oper_unification_3) { 

    TSet set(1);

    TSet set2(2);

    try {
        TSet set3 = set + set2;
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The maximum powers do not match");
    }
}
////////////

TEST(Test_Tset3, Oper_intersection) { 
    TSet set(4);
    set.InsElem(0);

    TSet set2(4);
    set2.InsElem(0);
    set2.InsElem(1);

    TSet set3 = set * set2;
    EXPECT_EQ(set3.IsMember(0), 1);
    EXPECT_EQ(set3.IsMember(1), 0);
}

TEST(Test_Tset3, Oper_intersection_1) {
    TSet set(4);
    set.InsElem(0);

    TSet set2 = set * set;
    EXPECT_EQ(set2.IsMember(0), 1);
    EXPECT_EQ(set2.IsMember(1), 0);
}

TEST(Test_Tset3, Oper_intersection_2) {
    TSet set(0);

    TSet set2(0);

    TSet set3 = set * set2;
    EXPECT_EQ(set3.GetMaxPower(), 0);
}
////////
TEST(Test_Tset4, Oper_output) {
    TSet set(4);
    set.InsElem(0);
    set.InsElem(2);
    std::ostringstream s;
    s << set;
    EXPECT_EQ(s.str(), "0101: {0,2}");
}

TEST(Test_Tset4, Oper_output_1) {
    TSet set(4);
    set.InsElem(0);
    set.InsElem(2);

    TSet set2(3);
    set2.InsElem(0);

    std::ostringstream s;
    s << set << "; " << set2;
    EXPECT_EQ(s.str(), "0101: {0,2}; 001: {0}");
}

TEST(Test_Tset4, Oper_output_2) {
    TSet set(0);
    try {
        std::cout << set;
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The maximum power of the set is 0. There are no elements that can be added");
    }
}
///////
TEST(Test_Tset4, Oper_input) {
    TSet set(4);
    std::istringstream in("0,2,3");
    in >> set;
    EXPECT_EQ(set.IsMember(0), 1);
    EXPECT_EQ(set.IsMember(1), 0);
    EXPECT_EQ(set.IsMember(2), 1);
    EXPECT_EQ(set.IsMember(3), 1);
}

TEST(Test_Tset4, Oper_input_0) {
    TSet set(0);
    std::istringstream in("0,2,4");

    try {
        in >> set;
    }
    catch (const std::runtime_error& a) {
        EXPECT_STREQ(a.what(), "The maximum power of the set is 0. There are no elements that can be added");
    }
}

TEST(Test_Tset4, Oper_input_1) {
    TSet set(4);
    std::istringstream in("0,2,4");

    try {
        in >> set;
    }
    catch (const std::out_of_range& a) {
        EXPECT_STREQ(a.what(), "Incorrect index. The boundaries of the universal set");
    }
}

TEST(Test_Tset4, Oper_input_2) {
    TSet set(4);
    std::istringstream in("0,2a3");

    try {
        in >> set;
    }
    catch (const std::invalid_argument& a) {
        EXPECT_STREQ(a.what(), "Incorrect index. Incorrect symbol");
    }
}

TEST(Test_Tset4, Oper_input_3) {
    TSet set(5);
    std::istringstream in("0,-1");
    try {
        in >> set;
    }
    catch (const std::invalid_argument& a) {
        EXPECT_STREQ(a.what(), "Incorrect index. Incorrect symbol");
    }
}

TEST(Test_Tset4, Oper_input_4) {
    TSet set(110);
    std::istringstream in("1,108");
    in >> set;
    EXPECT_EQ(set.IsMember(1), 1);
    EXPECT_EQ(set.IsMember(108), 1);
}

TEST(Test_Tset4, Oper_input_5) {
    TSet set(4);
    std::istringstream in("0 2 3");

    try {
        in >> set;
    }
    catch (const std::invalid_argument& a) {
        EXPECT_STREQ(a.what(), "Incorrect index. Incorrect symbol");
    }
}

TEST(Test_Tset4, Oper_input_6) { 
    TSet set(4);
    std::istringstream in("0,,,2,3");

    try {
        in >> set;
    }
    catch (const std::runtime_error& a) {

        EXPECT_STREQ(a.what(), "Error. Empty values between commas are not allowed");
    }
}

TEST(Tset_Tset4, Oper_input_7) { 
    TSet set(4);
    std::istringstream in(",0,1");
    try {
        in >> set;
    }
    catch (const std::runtime_error& a) {

        EXPECT_STREQ(a.what(), "Error. Empty values between commas are not allowed");
    }
}
//////////
