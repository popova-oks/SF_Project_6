#include "../headers/sha1.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


uint cycle_shift_left(uint val, int bit_count) {
    return (val << bit_count | val >> (32-bit_count));
}

uint bring_to_human_view(uint val) {
    return  ((val & 0x000000FF) << 24) | 
            ((val & 0x0000FF00) << 8) | 
            ((val & 0x00FF0000) >> 8) | 
            ((val & 0xFF000000) >> 24);
}

std::string sha1(const std::string &password) {
    // Инициализация
    uint A = H[0];
    uint B = H[1];
    uint C = H[2];
    uint D = H[3];
    uint E = H[4];
    
    // Подсчет размера сообщения в байтах
    uint msize_bytes = password.size();
    uint totalBlockCount = msize_bytes / one_block_size_bytes;
    
    // Подсчет, сколько байт нужно, чтобы дополнить последний блок
    uint needAdditionalBytes = one_block_size_bytes - (msize_bytes % one_block_size_bytes);
    
    if (needAdditionalBytes < 8) {
        totalBlockCount += 2;
        needAdditionalBytes += one_block_size_bytes;
    } else {
        totalBlockCount += 1;
    }
    
    // Размер дополненного сообщения
    uint extendedMessageSize = msize_bytes + needAdditionalBytes;
    
    // Создаем и заполняем буфер сообщения
    std::vector<unsigned char> newMessage(extendedMessageSize, 0);
    std::copy(password.begin(), password.end(), newMessage.begin());
    
    // Первый бит ставим '1', остальные обнуляем
    newMessage[msize_bytes] = 0x80;
    
    // Устанавливаем длину исходного сообщения в битах
    uint* ptr_to_size = reinterpret_cast<uint*>(&newMessage[extendedMessageSize - 4]);
    *ptr_to_size = bring_to_human_view(msize_bytes * 8);
    
    ExpendBlock exp_block;
    
    // Раунды
    for (int i = 0; i < totalBlockCount; i++) {
        // Текущий блок
        unsigned char* cur_p = &newMessage[one_block_size_bytes * i];
        Block block = reinterpret_cast<Block>(cur_p);
        
        // Первые 16 4-байтовых чисел
        for (int j = 0; j < one_block_size_uints; j++) {
            exp_block[j] = bring_to_human_view(block[j]);
        }
        
        // Следующие 64...
        for (int j = one_block_size_uints; j < block_expend_size_uints; j++) {
            exp_block[j] = exp_block[j-3] ^ exp_block[j-8] ^ exp_block[j-14] ^ exp_block[j-16];
            exp_block[j] = cycle_shift_left(exp_block[j], 1);
        }
            
        // Инициализация 
        uint a = H[0];
        uint b = H[1];
        uint c = H[2];
        uint d = H[3];
        uint e = H[4];

        // Пересчитываем
        for (int j = 0; j < block_expend_size_uints; j++) {
            uint f;
            uint k;
            // В зависимости от раунда считаем по-разному
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
        
            // Перемешивание
            uint temp = cycle_shift_left(a, 5) + f + e + k + exp_block[j];
            e = d;
            d = c;
            c = cycle_shift_left(b, 30);
            b = a;
            a = temp;   
        }
        // Пересчитываем
        A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
        E = E + e;
    }

   // Вычисление хэша
    uint digest[5] = {A, B, C, D, E};

    // Преобразование числовых значений в шестнадцатеричное представление и объединение в строку
    std::ostringstream result;
    result << std::hex << std::setfill('0');
    for (uint i : digest) {
        result << std::setw(8) << i;
    }    
    return result.str();;
}