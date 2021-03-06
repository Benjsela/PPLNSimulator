#This program simulates the reward system of PPLNS

import random;
import numpy as np
from scipy.stats import poisson

N1 = 5000; #Length of N in PPLNS of MP1
N2 = 5000; #Length of N in PPLNS of MP2
Lambda_1 = 20; #arrival rate of shares per round in MP1;
Lambda_2 = 25; #arrival rate of shares per round in MP2;
Lambda_3 = 40; #arrival rate of shares per round in other mining pool;

Rounds = 500; #num of rounds between two blocks;
Block_num = 1000;
reward1 = 0;  #Player 1 always stays in MP1
reward2 = 0; #Player 2 (Attacker) can hop within MP1 and MP2
MP_P2 = 1;
Portion = 0.07;

Q1 = [];
Q2 = [];

def fill(p, queue, N):
	while len(queue)<N:
		if random.random()<p:
			queue.append(1);
		elif random.random()<2*p:
			queue.append(2);
		else:
			queue.append(0);


#initialization
fill(Portion*20/10, Q1, N1);
print(len(Q1));
Q2 = [0]*N2;
Block_index = 0;
#Pool1_win = 0;

while Block_index <= Block_num:
	Block_index = Block_index + 1;
	Lambda_1 = random.uniform(9.8,10.2);
	Lambda_2 = random.uniform(9.8,10.2);
	Lambda_3 = 100 - Lambda_1 - Lambda_2;
	#Decision_round = Rounds - random.randint(145,155);
	j = 0;
	#Decision_round = random.randint(1,Rounds);
	Decision_round = 1;  
	while True:
		if random.random()<= 1.0/Rounds:   #At the beginning of each round, check if a block is found, if yes, break the loop
			break;
		j = j+1;
		s_1 = np.random.poisson(Lambda_1); #Number of shares arriving at MP1
		s_2 = np.random.poisson(Lambda_2); #Number of shares arriving at MP2
		if j==Decision_round:              #The attacker decides whether or not to hop
			mu_1 = Lambda_1*Rounds;
			mu_2 = Lambda_2*Rounds;
			MP1_ExpectedPayoff = (mu_1*poisson.cdf(N1-2,mu_1)+N1*(1-poisson.cdf(N1-1,mu_1)))/N1;
			MP2_ExpectedPayoff = (mu_2*poisson.cdf(N2-2,mu_2)+N2*(1-poisson.cdf(N2-1,mu_2)))/N2;
			pre_MP = MP_P2;
			if MP1_ExpectedPayoff>MP2_ExpectedPayoff:
				MP_P2 = 1;
			else:
				MP_P2 =2;
			if pre_MP != MP_P2:
				if MP_P2 == 1:
					Lambda_1 = Lambda_1 + Portion * 20;
					Lambda_2 = Lambda_2 - Portion * 20;
				else:
					Lambda_1 = Lambda_1 - Portion * 20;
					Lambda_2 = Lambda_2 + Portion * 20;
		
		tmp = [];
		for m in range(s_1):
			R = random.random();  
			if R<Portion*20/Lambda_1:
				tmp.append(1);
			elif R<Portion*2*20/Lambda_1 and MP_P2 == 1: #If R is between 0.01 - 0.02 and Player2 is in MP1, she gets on share.
				tmp.append(2);
			else:
				tmp.append(0);		
		Q1 = Q1[s_1:]+tmp;

		tmp = [];
		
		for m in range(s_2):
			if random.random()<Portion*20/Lambda_2 and MP_P2 == 2:
				tmp.append(2);
				#print "hahahaah";
			else:
				tmp.append(0);		
		Q2 = Q2[s_2:]+tmp;
		
	R = random.random();	
	#print Lambda_1, Lambda_2, Lambda_3;
	if R<float(Lambda_1)/(Lambda_1+Lambda_2+Lambda_3): #Determine the pool to mine the next block and pay for the shars in Queue
		#print "hahahaah";
		#Pool1_win = Pool1_win + 1;
		reward1 += float(Q1.count(1))/N1;
		reward2 += float(Q1.count(2))/N1;
	
	elif R<float(Lambda_1+Lambda_2)/(Lambda_1+Lambda_2+Lambda_3):
		#print "ddddd";
		reward2 += float(Q2.count(2))/N2;
	
#print Pool1_win;
print reward1;
print reward2;





