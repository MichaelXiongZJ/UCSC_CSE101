# This script computes grades for CSE101 students. It only gives an "approximate" grade, since the plus/minus
# boundary is not yet decided.
# 
# USAGE: python3 grading-for-students.py
# OUTPUT: Approximate grade, printed to console.
# 
# It will prompt the student to enter grades (through the console) for the tests and for the HWs.
# 
# The output grade is printed out to the console, and is computed based on a simple decision tree.
# 
# C. Seshadhri, Nov 2021

import sys
import os

test_str = input('Enter your test scores, with spaces between the scores: ') # get the string of test scores
hw_str = input('Enter your homework scores, with spaces between the scores: ') # get the string of HW scores
test_tokens = (test_str.strip()).split() # tokenize the test scores by whitespace
hw_tokens = (hw_str.strip()).split() # tokenize the HW scores by whitespace

test_scores = list() # initialize list of test scores
hw_scores = list() # initialize list of HW scores

num_tests = 5 # just setting the constants for number of tests and hws
num_hw = 4

# loop over test_tokens to get the test scores
for i in range(1,num_tests+1): # start loop from 1, to make indexing easier
    if (i > len(test_tokens)): # user did not provide score for this test
        print('You did not give a score for Test '+str(i)+', so setting score to zero\n')
        test_scores.append(0)
    else: # user did give score, so append
        test_scores.append(int(test_tokens[i-1])) # note the off by one, since i indexes the test number, which is one less than the array index. Also this line may throw exception if score provided is not integer


# loop over hw_tokens to get HW scores
for i in range(1,num_hw+1): # start loop from 1, to make indexing easier
    if (i > len(hw_tokens)): # user did not provide score for this HW
        print('You did not give a score for HW '+str(i)+', so setting score to zero\n')
        hw_scores.append(0)
    else: # user did give score, so append
        hw_scores.append(int(hw_tokens[i-1])) # note the off by one, since i is the HW number. Line may throw exception if score is not integer

test_total = sum(test_scores) - min(test_scores)# this is the normalized test score, obtained by removing the worst test. Total is out of 40

hw_total = float(4*sum(hw_scores) - 3*min(hw_scores))/float(4*num_hw - 3) # normalize hw scores, obtained by downweighting worst hw to one-fourth. Total is out of 10

# now for the decision tree

if test_total < 28:
    print('Sorry, you will not pass the course')
else: # student will pass the course. Now we determine the grade
    if hw_total < 2.5: # low score on HW
        if test_total < 35: # ok performance on tests
            print('You will get a C.')
        else: # test total is good
            print('You will get at least a B-')
    if hw_total >= 2.5 and hw_total < 4.5: # ok performance on HW
        print('You will get at least a B-')
    if hw_total >= 4.5 and hw_total < 8.5: # good performance on HW
        print('You will get at least a B')
    if hw_total >= 8.5: # strong performance on HW
        if test_total < 35: # ok performance on tests
            print('You will get at least a B+')
        else: # strong performance on HW and tests
            print('You will get at least an A-')

print('\nI will decide the plusses and minuses at the end of the quarter')
