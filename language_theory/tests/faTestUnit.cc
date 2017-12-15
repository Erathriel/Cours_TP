#include "../include/fa.h"
#include "include/gtest/gtest.h"

// Test creation et destruction d'un automate
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

// Test configurer un etat initial
TEST(faTest, setInitialState){
	struct fa test;

	fa_create(&test,2,5);

	fa_set_state_initial(&test,1);

	EXPECT_TRUE(test.states[1].is_initial);
	EXPECT_FALSE(test.states[0].is_initial);

	fa_destroy(&test);
}

// Test configurer un etat final
TEST(faTest, setFinalState){
	struct fa test;

	fa_create(&test,2,5);

	fa_set_state_final(&test,1);

	EXPECT_TRUE(test.states[1].is_final);
	EXPECT_FALSE(test.states[0].is_final);

	fa_destroy(&test);
}

// Test configurer un etat initial et final
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

// Test ajout de transition
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

// Test suppression de transition
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

// Test du comptage du nombre de transition
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

// Test verification du determinisme d'un automate
TEST(faTest, deterministic){
	struct fa test;

    fa_create(&test,2,3);
    fa_add_transition(&test,0,'a',1);
    fa_add_transition(&test,0,'a',2);

    EXPECT_FALSE(fa_is_deterministic(&test));

    fa_remove_transition(&test,0,'a',2);
    fa_add_transition(&test,0,'b',2);

    EXPECT_TRUE(fa_is_deterministic(&test));

    fa_destroy(&test);
}

// Test verifie si un automate est complet ou non
TEST(faTest, complete){
	struct fa test2;

	fa_create(&test2,1,2);

	fa_add_transition(&test2,0,'a',1);
	fa_add_transition(&test2,1,'a',0);
	EXPECT_TRUE(fa_is_complete(&test2));

	fa_destroy(&test2);
	fa_create(&test2,1,2);

	fa_add_transition(&test2,0,'a',1);
	EXPECT_FALSE(fa_is_complete(&test2));

	fa_destroy(&test2);

}

// Test rendre un automate complet
TEST(faTest, makeComplete){
	struct fa test2;

	fa_create(&test2,1,2);

	fa_add_transition(&test2,0,'a',1);
	fa_add_transition(&test2,1,'a',0);

	fa_make_complete(&test2);

	EXPECT_TRUE(fa_is_complete(&test2));

	fa_destroy(&test2);

	/*fa_create(&test2,1,2);

	fa_add_transition(&test2,0,'a',1);

	fa_make_complete(&test2);

	EXPECT_TRUE(fa_is_complete(&test2));

	fa_destroy(&test2);*/
}

// creation et destruction de graphe
TEST(faTest, createDestroyGraphFromFa){
	struct fa test;
	struct graph g;

	fa_create(&test,2,3);

	graph_create_from_fa(&g, &test, true);
	EXPECT_EQ(g.size,3);
	for (int i = 0; i < g.size; ++i)
	{
		for (int j = 0; j < g.size; ++j)
		{
			EXPECT_FALSE(g.transition[i][j]);
		}
	}
	graph_destroy(&g);
	fa_destroy(&test);

	fa_create(&test,2,3);
	fa_add_transition(&test,0,'a',1);

	graph_create_from_fa(&g, &test, true);
	EXPECT_TRUE(g.transition[0][1]);

	graph_destroy(&g);
	fa_destroy(&test);
}

// Test parcours profondeur
TEST(faTest, depthFirstSearch){
	struct fa test;
	struct graph g;

	fa_create(&test,2,3);
	fa_add_transition(&test,0,'a',1);

	graph_create_from_fa(&g, &test, true);
	//graph_depth_first_search(&g, 1, true);

	graph_destroy(&g);
	fa_destroy(&test);
}

// Test chemin existant ou non
TEST(faTest, hasPath){
	struct fa test;
	struct graph g;

	fa_create(&test,2,3);
	fa_add_transition(&test,0,'a',1);
	graph_create_from_fa(&g, &test, true);
	EXPECT_TRUE(graph_has_path(&g, 0, 1));
	EXPECT_TRUE(graph_has_path(&g, 0, 0));
	EXPECT_FALSE(graph_has_path(&g, 0, 2));


	graph_destroy(&g);
	fa_destroy(&test);	
}

TEST(faTest, languageEmpty){
	struct fa test;

	fa_create(&test,2,3);
	fa_add_transition(&test,0,'a',1);
	EXPECT_FALSE(fa_is_language_empty(&test));

	fa_destroy(&test);

	fa_create(&test,2,3);
	fa_set_state_initial(&test,0);
	fa_set_state_final(&test,1);

	EXPECT_TRUE(fa_is_language_empty(&test));

	fa_destroy(&test);
}