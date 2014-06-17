#include "ComputerPlayer.h"

void ComputerPlayer::play() {
	vector<Card*> validCardsToPlay = getLegalPlays();
	vector<Card*> playerHand = _cards.hand();
	for(int i=0;i<playerHand.size();i++){
		for(int j=0;j<validCardsToPlay.size();j++){
			if(playerHand.at(i) == validCardsToPlay.at(j)){
				cout << "Player " << playerNumber() << " plays " << playerHand.at(i) << endl;
				_cards.removeCard(_cards.hand().begin()+i);
				return;
			}
		}
	}
	//if we get here, there was no valid play, so discard first card in hand
	discard(playerHand.at(0));
}

void ComputerPlayer::print() const {

}