#include <iostream>
#include <Vector.h>
#include "Player.h"

std::string GetRandomName()
{
    static std::string names[] =
    {
        "Robert", "Carlos", "Enzo", "Giovanni", "Luiz",
        "Joao", "David", "Sophia", "Lucas", "Olivia",
        "Benjamin", "Gus", "Ethan", "Liam", "Mia",
        "Dilan", "Leo", "Daniel", "Juan", "Henry"
    };

    return names[rand() % 20];
}

int main()
{
    Vector<Player> players;

    for (int i = 0; i < 10; i++)
    {
        players.PushBack(Player(GetRandomName()));
    }
    
    for (int i = 0; i < players.Size(); i++)
    {
        players[i].DisplayInfo();
    }

    std::cout << "\n\n Removing 6 Players \n\n";

    players.Resize(4);

    for (int i = 0; i < players.Size(); i++)
    {
        players[i].DisplayInfo();
    }

    std::cout << "\n\n Add max 20 \n\n";

    while (players.Size() < 20)
    {
        players.PushBack(Player(GetRandomName()));
    }

    for (int i = 0; i < players.Size(); i++)
    {
        players[i].DisplayInfo();
    }

    int indexA = rand() % players.Size();
    int indexB;

    do
    {
        indexB = rand() % players.Size();
    } while (indexA == indexB);

    Player playerA = players[indexA];
    Player playerB = players[indexB];

    int scoreA =
        playerA.GetStats(Health) - ((playerB.GetStats(Attack) * playerB.GetStats(Stamina)) -
            (playerA.GetStats(Defense) * playerA.GetStats(Speed)));

    int scoreB = playerB.GetStats(Health) - ((playerA.GetStats(Attack) * playerA.GetStats(Stamina)) -
        (playerB.GetStats(Defense) * playerB.GetStats(Speed)));

    std::cout << "\n\n========== FIGHT ==========\n";
    std::cout << playerA.GetName() << " Score: " << scoreA << "\n";
    std::cout << playerB.GetName() << " Score: " << scoreB << "\n\n";

    if (scoreA > scoreB)
    {
        std::cout << "Winner: " << playerA.GetName() << "\n";
    }
    else if (scoreB > scoreA)
    {
        std::cout << "Winner: " << playerB.GetName() << "\n";
    }
    else
    {
        std::cout << "Tie! Flipping a coin...\n";

        if (rand() % 2 == 0)
            std::cout << "Winner: " << playerA.GetName() << "\n";
        else
            std::cout << "Winner: " << playerB.GetName() << "\n";
    }

    return 0;
}