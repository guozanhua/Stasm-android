#include <jni.h>
#include <string>
#include <opencv/cv.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "stasm_lib.h"
#include "stasm/stasm_lib.h"
#include <android/log.h>


#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,"MainActivity",__VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnitest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnitest_MainActivity_loadJpeg(JNIEnv *env, jobject instance, jstring root_,
                                               jstring path_) {
    const char *root = env->GetStringUTFChars(root_, 0);
    const char *path = env->GetStringUTFChars(path_, 0);
    clock_t start, finish;

    cv::Mat_<unsigned char> img(cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE));
    int foundface;
    float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)
    char data[] = "/test";
    char new_jpg[] = "/test/minimal.jpg";

    char *data_path = new char[strlen(root) + strlen(data) + 1];
    strcpy(data_path, root);
    strcat(data_path, data);


    stasm_search_single(&foundface, landmarks, (const char *) img.data, img.cols, img.rows, path,
                        data_path);
    start = clock();
    if (foundface) {
        stasm_force_points_into_image(landmarks, img.cols, img.rows);
        for (int i = 0; i < stasm_NLANDMARKS; i++) {
            LOGW(" for = %d", i);
            int x = cvRound(landmarks[i * 2 + 1]);
            int y = cvRound(landmarks[i * 2]);
            img(x, y) = 255;
        }
        finish = clock();
        LOGW("spend = %ld", (finish - start));
        char *new_jpg_path = new char[strlen(root) + strlen(new_jpg) + 1];
        strcpy(new_jpg_path, root);
        strcat(new_jpg_path, new_jpg);
        std::string new_file = new_jpg_path;
        cv::imwrite(new_file, img);
        delete[](new_jpg_path);
    }
    delete[](data_path);
    env->ReleaseStringUTFChars(root_, root);
    env->ReleaseStringUTFChars(path_, path);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnitest_MainActivity_loadMoreFaceJpeg(JNIEnv *env, jobject instance, jstring root_,
                                                       jstring path_) {
    const char *root = env->GetStringUTFChars(root_, 0);
    const char *path = env->GetStringUTFChars(path_, 0);


    char data[] = "/test";
    char new_jpg[] = "/test/minimal2.jpg";

    char *data_path = new char[strlen(root) + strlen(data) + 1];
    strcpy(data_path, root);
    strcat(data_path, data);
    clock_t start, finish;
    start = clock();
    int init = stasm_init(data_path, 0 /*trace*/);
    cv::Mat_<unsigned char> img(cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE));


    stasm_open_image((const char *) img.data, img.cols, img.rows, path, 1, 10);

    int foundface;
    float landmarks[2 * stasm_NLANDMARKS];

    int nfaces = 0;
    while (1) {
        stasm_search_auto(&foundface, landmarks);

        if (!foundface)
            break;
        stasm_convert_shape(landmarks, 68);
        stasm_force_points_into_image(landmarks, img.cols, img.rows);
        for (int i = 0; i < stasm_NLANDMARKS; i++)
            img(cvRound(landmarks[i * 2 + 1]), cvRound(landmarks[i * 2])) = 255;
        nfaces++;
    }
    finish = clock();
    LOGW("face number = %d", nfaces);
    LOGW("spend = %d", (finish - start));
    char *new_jpg_path = new char[strlen(root) + strlen(new_jpg) + 1];
    strcpy(new_jpg_path, root);
    strcat(new_jpg_path, new_jpg);
    std::string new_file = new_jpg_path;
    cv::imwrite(new_file, img);
    delete[](new_jpg_path);
    delete[](data_path);
    env->ReleaseStringUTFChars(root_, root);
    env->ReleaseStringUTFChars(path_, path);
}