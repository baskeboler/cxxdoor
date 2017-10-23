#include <gtest/gtest.h>
#include <folly/init/Init.h>
#include <glog/logging.h>

int main(int argc, char *argv[])
{
    google::InstallFailureSignalHandler();
    folly::init(&argc, &argv);
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}

