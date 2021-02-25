int ComputeMaxSteal(int* cards, int cash, int subsets, int bits){
        int maxSteal = 0;
        int* items;
        int* optimal;
        int totCost = 0;
	int newCost = 0;
	int sntl = 0;
        numCards = sizeof(cards)/sizeof(cards[0]);
        for(int i = 0; i < numCards; i++){
                totCost = totCost + cards[i];
        }
        if(totCost <= cash){
                return totCost;
        }
	else totCost = 0;
        for(int i = 0; i < subsets; i++){
		for(int j = 0; j < bits; j++){
			if((i >> j) & 1){
				items[sntl] = cards[j];
				sntl++;
			}
		}
		for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
			newCost = newCost + items[r];
		}
		if(newCost < cash){
			if(newCost > maxSteal){
				maxSteal = newCost;
				newCost = 0;
				for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
                        		optimal[r] = items[r];
					items[r] = 0;
                		}
			}
		}
	}
	return maxProfit;
}
