#include "../include/fa.h"
#include "include/gtest/gtest.h"

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

TEST(faTest, addTransition){
	struct fa test;

	fa_create(&test,2,3);

	fa_add_transition(&test, 0,'b',2);

	EXPECT_EQ(test.transitions[0][1].size,1);
	EXPECT_EQ(test.transitions[0][0].size,0);
	EXPECT_EQ(test.transitions[2][0].size,0);
	EXPECT_EQ(test.transitions[2][1].size,0);
	EXPECT_EQ(test.transitions[0][1].capacity,3);
	EXPECT_EQ(test.transitions[0][0].capacity,0);
	EXPECT_EQ(test.transitions[2][1].capacity,0);
	EXPECT_EQ(test.transitions[2][0].capacity,0);
	EXPECT_EQ(test.transitions[0][0].states[2],0);
	EXPECT_EQ(test.transitions[0][1].states[2],1);
	EXPECT_EQ(test.transitions[2][0].states[0],0);
	EXPECT_EQ(test.transitions[2][1].states[0],0);

	fa_add_transition(&test, 0,'a',2);

	EXPECT_EQ(test.transitions[0][0].size,1);
	EXPECT_EQ(test.transitions[0][0].states[2],1);
	EXPECT_EQ(test.transitions[0][0].capacity,3);


	fa_add_transition(&test, 0,'a',0);

	EXPECT_EQ(test.transitions[0][0].size,2);
	EXPECT_EQ(test.transitions[0][0].states[0],1);
	EXPECT_EQ(test.transitions[0][0].capacity,3);


	fa_add_transition(&test, 2,'a',0);
	EXPECT_EQ(test.transitions[2][0].size,1);
	EXPECT_EQ(test.transitions[2][0].states[0],1);
	EXPECT_EQ(test.transitions[2][0].capacity,3);


	fa_destroy(&test);
}

TEST(faTest, removeTransition){
	struct fa test;

	fa_create(&test,2,3);

	fa_add_transition(&test, 0,'a',2);
	
	fa_remove_transition(&test, 0,'a',2);

	EXPECT_EQ(test.transitions[0][0].size,0);
	EXPECT_EQ(test.transitions[0][0].states[2],0);
	EXPECT_EQ(test.transitions[0][0].capacity,3);

	fa_destroy(&test);
}

TEST(faTest, removeState){
	struct fa test;

	fa_create(&test,2,3);

	fa_add_transition(&test, 0,'a',1);
	fa_add_transition(&test, 0,'b',2);
	fa_add_transition(&test, 2,'a',1);

	fa_remove_state(&test,2);
	EXPECT_EQ(test.transitions[2][0].size,0);
	EXPECT_EQ(test.transitions[2][0].states[1],0);

	fa_destroy(&test);
}

TEST(faTest, countTransition){
	struct fa test;

	fa_create(&test,2,3);
	int i = fa_count_transitions(&test);
	EXPECT_EQ(i,0);

	fa_add_transition(&test, 0,'a',2);
	i = fa_count_transitions(&test);
	EXPECT_EQ(i,1);

	fa_remove_transition(&test, 0,'a',2);
	i = fa_count_transitions(&test);
	EXPECT_EQ(i,0);

	fa_destroy(&test);		
}