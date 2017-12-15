#include "../include/fa.h"
#include "include/gtest/gtest.h"

/*TEST(test, test){
	EXPECT_TRUE(true);
}
*/

TEST(faTest, faCreateDestroy){
	struct fa test;

	fa_create(&test,2,5);

	EXPECT_EQ(test.state_count, 5);
	EXPECT_EQ(test.alpha_count, 2);

	fa_destroy(&test);

	fa_create(&test,4,3);

	EXPECT_EQ(test.state_count, 3);
	EXPECT_EQ(test.alpha_count, 4);

	fa_destroy(&test);
}

TEST(faTest, setInitialState){
	struct fa test;

	fa_create(&test,2,5);

	fa_set_state_initial(&test,1);

	EXPECT_TRUE(test.states[1].is_initial);
	EXPECT_FALSE(test.states[0].is_initial);

	fa_destroy(&test);
}

TEST(faTest, setFinalState){
	struct fa test;

	fa_create(&test,2,5);

	fa_set_state_final(&test,1);

	EXPECT_TRUE(test.states[1].is_final);
	EXPECT_FALSE(test.states[0].is_final);

	fa_destroy(&test);
}

TEST(faTest, setFinalInitialState){
	struct fa test;

	fa_create(&test,2,5);
	fa_set_state_initial(&test,1);
	fa_set_state_final(&test,1);

	EXPECT_TRUE(test.states[1].is_final);
	EXPECT_FALSE(test.states[0].is_final);
	EXPECT_TRUE(test.states[1].is_final);
	EXPECT_FALSE(test.states[0].is_final);

	fa_destroy(&test);
}

