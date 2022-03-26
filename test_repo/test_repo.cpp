#include "../inc/repository.h"
#include <unity/unity.h>

repository *test_repo;
void setUp()
{
}

void tearDown()
{
}

void test_open_file()
{
    int32_t fret = 0;
    fret = test_repo->open_file();
    TEST_ASSERT_EQUAL(0, fret);
}

void test_close_file()
{
    int32_t fret = -1;
    fret = test_repo->close_file();

    TEST_ASSERT_EQUAL(0, fret);
}

void test_set_data()
{
    int32_t fret = -1;

    fret = test_repo->set_data("LED_RED_STATUS", "ON");
    TEST_ASSERT_EQUAL(0, fret);

    fret = test_repo->set_data("LED_BLUE_STATUS", "ON");
    TEST_ASSERT_EQUAL(0, fret);

    fret = test_repo->set_data("LED_GREEN_STATUS", "ON");
    TEST_ASSERT_EQUAL(0, fret);

    fret = test_repo->set_data("LED_BLACK_STATUS", "ON");
    TEST_ASSERT_EQUAL(0, fret);

    fret = test_repo->set_data("LED_BLACK_STATUS", "ON");

    TEST_ASSERT_EQUAL(-1, fret);
}

void test_get_data()
{
    std::string data;
    std::string key = "LED_BLUE_STATUS";
    int32_t fret = -1;
    fret = test_repo->get_data(key, data);
    TEST_ASSERT_EQUAL(0, fret);
    std::clog<<key<<"-->"<<data<<std::endl;
}

void test_del_data()
{
    int32_t fret = -1;


    TEST_ASSERT_EQUAL(0, fret);
}

int main()
{
    test_repo = new repository("test_repo.txt");
    UNITY_BEGIN();
    RUN_TEST(test_open_file);
    RUN_TEST(test_set_data);
    RUN_TEST(test_get_data);
    RUN_TEST(test_del_data);
    RUN_TEST(test_close_file);
    delete  test_repo;
    return UNITY_END();

}
