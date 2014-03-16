// A very rough C++ version for the 2048 game
//
// Author: Olafur Waage / @olafurw
// olafurw@gmail.com
//
// Under the Apache License
// If you have any fun with this, please let me know, I would love to hear from you.

#include <iostream>

#include "grid.hpp"

unsigned int tournament_selection(const std::vector<grid>& population)
{
    std::uniform_int_distribution<> dis(0, population.size() - 1);

    unsigned int parent_a = dis(rand_gen());
    int parent_a_score = population[parent_a].score();

    unsigned int parent_b = dis(rand_gen());
    int parent_b_score = population[parent_b].score();

    return parent_a_score > parent_b_score ? parent_a : parent_b;
}

void mutation(std::vector<direction>& child_a_actions)
{
    std::uniform_int_distribution<> dis(0, 99);

    for(unsigned int i = 0; i < child_a_actions.size(); ++i)
    {
        if(dis(rand_gen()) < 10)
        {
            child_a_actions[i] = rand_action();
        }
    }
}

void one_point_crossover(const std::vector<direction>& parent_a,
                         const std::vector<direction>& parent_b,
                         grid& child_a,
                         grid& child_b)
{
    std::uniform_int_distribution<> dis(0, parent_a.size());

    std::vector<direction> child_a_actions;
    std::vector<direction> child_b_actions;

    unsigned int split_a = dis(rand_gen());
    unsigned int smaller_parent = std::min(parent_a.size(), parent_b.size());
    unsigned int larger_parent = std::max(parent_a.size(), parent_b.size());
    unsigned int split = std::min(split_a, smaller_parent);

    for(unsigned int i = 0; i < smaller_parent; ++i)
    {
        if(i < split)
        {
            child_a_actions.push_back(parent_a.at(i));
            child_b_actions.push_back(parent_b.at(i));
        }
        else
        {
            child_a_actions.push_back(parent_b.at(i));
            child_b_actions.push_back(parent_a.at(i));
        }
    }

    // TODO: Refactor, doing this now since each
    // child can be of different lengths
    // and the split can be in the larger parent
    for(unsigned int i = smaller_parent; i < larger_parent; ++i)
    {
        if(i < split)
        {
            if(larger_parent == parent_b.size())
            {
                child_a_actions.push_back(parent_b.at(i));
            }
            else
            {
                child_b_actions.push_back(parent_b.at(i));
            }
        }
        else
        {
            if(larger_parent == parent_b.size())
            {
                child_a_actions.push_back(parent_b.at(i));
            }
            else
            {
                child_b_actions.push_back(parent_a.at(i));
            }
        }
    }

    mutation(child_a_actions);
    mutation(child_b_actions);

    child_a.add_actions(child_a_actions);
    child_b.add_actions(child_b_actions);
}

void sort_population(std::vector<grid>& population)
{
    std::sort(population.begin(), population.end(),
        [](const grid & a, const grid & b)
    {
        return a.score() > b.score();
    });
}

void sort_population_random(std::vector<grid>& population)
{
    std::shuffle(population.begin(), population.end(), rand_gen());
}

int main()
{
    // Initial population
    std::vector<grid> population;

    int largest = 0;

    for(int i = 0; i < 100; ++i)
    {
        grid g;

        while(g.can_move())
        {
            g.action(rand_action());
        }

        population.emplace_back(g);
    }

    for(unsigned int i = 0; i < 100000; ++i)
    {
        unsigned int parent_a = tournament_selection(population);
        unsigned int parent_b = tournament_selection(population);

        grid child_a;
        grid child_b;

        one_point_crossover(population.at(parent_a).actions(),
                            population.at(parent_b).actions(),
                            child_a,
                            child_b);

        population.emplace_back(child_a);
        population.emplace_back(child_b);

        sort_population(population);

        population.pop_back();
        population.pop_back();

        if(largest < population.at(0).score())
        {
            largest = population.at(0).score();

            std::cout << largest << std::endl;
        }

        sort_population_random(population);
    }

    sort_population(population);

    population.at(0).print();

    for(auto const& p : population)
    {
        std::cout << p.score() << std::endl;
    }

    return 0;
}
