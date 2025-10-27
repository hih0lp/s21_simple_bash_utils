#!/bin/bash


echo "Tests"


echo "test line" > test1.txt
echo "test line 2" > test2.txt



echo "Test 1: one file"
./s21_cat test1.txt
echo ""

echo "Test 2: many files"
./s21_cat test1.txt test2.txt
echo ""

echo "Test 3: file dont exist"
./s21_cat somefile.txt test1.txt
echo ""

##############

echo "Test -n (--number) flag"
echo "line1" > test_n.txt
echo "" >> test_n.txt
echo "line2" >> test.n.txt
echo "testtesttesttesttest" >> test_n.txt

./s21_cat -n test_n.txt
echo "Default cat"
cat -n test_n.txt

echo "--number"

./s21_cat --number test_n.txt
echo "Default cat"
cat --number test_n.txt

##############

echo "Test -b (--number-nonblank) flag"
echo "line1" > test_b.txt
echo "" >> test_b.txt
echo "" >> test_b.txt
echo "line2" >> test_b.txt

./s21_cat -b test_b.txt
echo "Default cat"
cat -b test_b.txt

echo "--number-nonblank"

./s21_cat --number-nonblank test_b.txt
echo "Default cat"
cat --number-nonblank test_b.txt
echo ""

##############

echo "Test -s (--squeeze-blank) flag"

echo "line1" > test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "line4" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "" >> test_s.txt
echo "line" >> test_s.txt

./s21_cat -s test_s.txt
echo ""
cat -s test_s.txt

echo "squeeze-blank"

./s21_cat --squeeze-blank test_s.txt
echo "Default cat"
cat --squeeze-blank test_s.txt
echo ""

################

echo "Test -e -E -t -T flags"

echo -e "hello\t\tworld" > test_spec.txt
echo -e "line2\a" >> test_spec.txt
echo -e "line3" >> test_spec.txt

echo "Test -e"
./s21_cat -e test_spec.txt
echo "Default cat"
cat -e test_spec.txt

echo ""

echo "Test -E"
./s21_cat -E test_spec.txt
echo "Default cat"
cat -E test_spec.txt

echo ""

echo "Test -t"
./s21_cat -t test_spec.txt
echo "Default cat"
cat -t test_spec.txt

echo ""

echo "Test -T"
./s21_cat -T test_spec.txt
echo "Default cat"
cat -T test_spec.txt

