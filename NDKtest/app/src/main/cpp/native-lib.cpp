#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "md5.c"

//密钥
#define PASS  "KSVR9bbYixtDU4PdjgaZ78OJMxZkPNXo7aDSPYeIYZA="

void setChar(int *arg1) {

    switch (*arg1) {
        case 10:
            *arg1 = 97;
            break;
        case 11:
            *arg1 = 98;
            break;
        case 12:
            *arg1 = 99;
            break;
        case 13:
            *arg1 = 100;
            break;
        case 14:
            *arg1 = 101;
            break;
        case 15:
            *arg1 = 102;
            break;
        default:
            *arg1 = *arg1 + 48;
            break;
    }
}

char * transformChar(unsigned char *arg) {
    char enstr[33];
    char *dest_str;
    for (int i = 0; i < 16; ++i) {
        int c1 = arg[i] / 16;
        setChar(&c1);
        int c2 = arg[i] % 16;
        setChar(&c2);
        char c3 = c1;
        char c4 = c2;
        enstr[i * 2] = c3;
        enstr[i * 2 + 1] = c4;
    }
    enstr[32] = '\0';
    dest_str = (char *) calloc(sizeof(enstr), sizeof(char));
   // dest_str = (char *)malloc(sizeof(char) * (sizeof(enstr)));

    /* 为字符串分配堆空间 */
    strncpy(dest_str, enstr, sizeof(enstr));
    // 用C标准库函数strncpy拷贝字符
    return dest_str;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jiang_ndktest_JniUtils_getString(
        JNIEnv *env,
        jobject jobject/* this */) {
    MD5_CTX md5;
    MD5Init(&md5);
    //int i;
    unsigned char encrypt[] = "admin";//21232f297a57a5a743894a0e4a801fc3
    unsigned char decrypt[16];
    MD5Update(&md5, encrypt, strlen((char *) encrypt));
    MD5Final(&md5, decrypt);
    printf("加密前:%s\n加密后:", encrypt);
    char *md5s;
    md5s = transformChar(&decrypt[0]);

    int i = 0;
    for (; i < 16; i++) {
        printf("%02x", decrypt[i]);
    }
    return env->NewStringUTF(md5s);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jiang_ndktest_JniUtils_getEncrypt(
        JNIEnv *env,
        jobject jobject/* this */, jstring password) {
    //定义加密的字符串
    char str[500];
    strcpy(str, PASS);
    //获取需要加密的字符串
    char *c_str = (char *) (env)->GetStringUTFChars(password, JNI_FALSE);
    strcat(str, c_str);
    strcat(str, PASS);
    MD5_CTX md5;
    MD5Init(&md5);
    //int i;
    unsigned char encrypt[] = "admin";//21232f297a57a5a743894a0e4a801fc3
    unsigned char decrypt[16];
    MD5Update(&md5, (unsigned char *) encrypt, strlen((char *) encrypt));

    MD5Final(&md5, decrypt);
    //定义需要返回的char*
    char *md5str;
    //将加密后的unsigned char数组转化为char* 返回
    md5str = transformChar(&decrypt[0]);
    //free(md5str);
    return env->NewStringUTF(md5str);
}






