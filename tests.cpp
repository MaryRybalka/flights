#include "gtest/gtest.h"
#include <fstream>
#include "lib.h"
#include <iostream>
using namespace std;

TEST(findMinWay, EmptyFile){
    string f = "ivan";
    string t = "klui";
    EXPECT_EQ(findMinWay("../testFiles/empty", f, t), MAX);
}

TEST(findMinWay, DoesntExistFile){
    string f = "ivan";
    string t = "klui";
    EXPECT_THROW(findMinWay("./src", f, t), bad_alloc);
}

TEST(records, DepartureError){
    ifstream f;
    f.open("../testFiles/depEr");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    int number = numbersOfRecords(check);
    auto *map = new Roads[number];
    EXPECT_THROW(records(check, map, number),out_of_range);
    delete[] (map);
}

TEST(records, ArrivalError){
    ifstream f;
    f.open("../testFiles/arEr");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    int number = numbersOfRecords(check);
    auto *map = new Roads[number];
    EXPECT_THROW(records(check, map, number),out_of_range);
    delete[] (map);
}

TEST(records, DistanceError){
    ifstream f;
    f.open("../testFiles/distEr");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    int number = numbersOfRecords(check);
    auto *map = new Roads[number];
    EXPECT_THROW(records(check, map, number),out_of_range);
    delete[] (map);
}

TEST(searchLess, DistanceBetweenTwoPoints){
    ifstream f;
    f.open("../testFiles/twoPoints");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    auto *map = new Roads[2];
    records(check, map, 2);
    string fr = "ivanovo";
    string t = "kluevo";
    EXPECT_EQ(searchLess(map, fr, t, 2), 11);
    delete[] (map);
}

TEST(searchLess, DistanceBetweenThreePoints){
    ifstream f;
    f.open("../testFiles/threePoints");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    auto *map = new Roads[4];
    records(check, map, 4);
    string fr = "ivanovo";
    string t = "vladivostok";
    EXPECT_EQ(searchLess(map, fr, t, 4), 15);
    delete[] (map);
}

TEST(searchLess, DistanceBetweenFourPoints){
    ifstream f;
    f.open("../testFiles/fourPoints");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    auto *map = new Roads[4];
    records(check, map, 4);
    string fr = "ivanovo";
    string t = "moskow";
    EXPECT_EQ(searchLess(map, fr, t, 4), 9015);
    delete[] (map);
}

TEST(searchLess, DistanceBetweenSomePoints){
    ifstream f;
    f.open("../src");
    string check((istreambuf_iterator<char>(f)),
                 istreambuf_iterator<char>());
    f >> check;
    f.close();
    int number = numbersOfRecords(check);
    auto *map = new Roads[number];
    records(check, map, number);
    string fr = "ivan";
    string t = "klui";
    EXPECT_EQ(searchLess(map, fr, t, number), 4);
    delete[] (map);
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Russian");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}