echo "=============Tests================="

############

echo ""
echo "Test -e pattern"
grep -e "main" s21_grep.c
./s21_grep -e "main" s21_grep.c

############

echo ""
echo "Test without options"
grep "main" s21_grep.c
./s21_grep "main" s21_grep.c

############

echo ""
echo "Test -i pattern"
grep -i "MaIN" s21_grep.c
./s21_grep -i "MaIN" s21_grep.c

############

echo ""
echo "Test -v pattern"
grep -v "main" s21_grep.c
./s21_grep -v "main" s21_grep.c

############

echo ""
echo "Test -c pattern"
grep -c "main" s21_grep.c
./s21_grep -c "main" s21_grep.c

############

echo ""
echo "Test -n pattern"
grep -n "main" s21_grep.c
./s21_grep -n "main" s21_grep.c

############

echo ""
echo "Test many files with different patterns"
grep -c "main" s21_grep.c test.txt
./s21_grep -c "main" s21_grep.c test.txt