//
// Created by sigris on 09.05.2024.
//

#include "lib/indexator/IndexatorProcessor.cpp"
// В качестве первого аргумента получаем директорию с файлами, которые хотим обходить
// второй аргумент - положение файла с итоговой информацией,
// а остальные аргументы формируют сам запрос

int main(int argc, char* argv[]) {
    int a = 2;
    char *b[2]{"/Users/sigris/AllLabsWithoutCmake", "/Users/sigris/Index"};
    IndexatorProcess(b[0], b[1]);
    return 0;
}