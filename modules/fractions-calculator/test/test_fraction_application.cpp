// Copyright 2019 Andronov Maxim

#include <gtest/gtest.h>

#include "include/fraction_application.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class FractionCalculatorTest : public ::testing::Test {
 protected:
    void Act(vector<string> args_) {
        vector<const char*> options;

        options.push_back("FractionCalculator");
        for (size_t i = 0; i < args_.size(); ++i) {
            options.push_back(args_[i].c_str());
        }

        const char** argv = &options.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

 private:
    FractionCalculator app_;
    string output_;
};

TEST_F(FractionCalculatorTest, Print_Help_If_No_Arguments) {
    vector<string> args = {};

    Act(args);

    Assert("This is a fraction calculator application\\..*");
}

TEST_F(FractionCalculatorTest, Can_Detect_Wrong_Number_Format) {
    vector<string> args = { "gh", "55", "qw", "584", "+" };

    Act(args);

    Assert("gh is not the number.*");
}



