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
        const std::vector<sf::Vector2u>& GetAttackableLocations()
        {
            return m_attackableLocations;
        }

    private:
        void UpdateLocationByNextStepOfTranslation();
        void UpdateAttackRangeOnMap(DiscreteMap* l_map) const;
        void GenerateAttackableLocations();

    private:
        std::vector<sf::Vector2u> m_translation;
        size_t m_attackRadius;
        size_t m_translationStep;
        std::vector<sf::Vector2u> m_attackableLocations;
};

#endif // _ENEMY_HPP_
