#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "MoveableObject.hpp"

class Enemy : public MoveableObject
{
    public:
        Enemy(const std::vector<sf::Vector2u>& l_translation, size_t l_attackRadius);
        virtual ~Enemy();

        virtual void Update(sf::Time dt) override;
        virtual void UpdateLocationOnMap(DiscreteMap* l_map) const override;
        virtual ObjectType GetObjectType() const override;

    private:
        void TranslationStepIteration();
        void UpdateAttackRangeOnMap(DiscreteMap* l_map) const;

    private:
        std::vector<sf::Vector2u> m_translation;
        size_t m_attackRadius;
        size_t m_translationStep;
};

#endif // _ENEMY_HPP_
