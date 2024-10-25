#include "EnemySystem.hpp"

EnemySystem::EnemySystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

EntityID EnemySystem::spawn(int variant) {
  auto enemy = scene->createEntity();
  std::cout << "enemy init: " << enemy << std::endl;
  enemies.push_back(enemy);
  BT::BehaviorTreeFactory factory;
  factory.registerSimpleCondition("InSight", [&, enemy](BT::TreeNode &) {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    auto sight = scene->getComponent<Sight>(enemy);
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < sight->sight ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  });
  factory.registerSimpleCondition("InRange", [&, enemy](BT::TreeNode &) {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    auto range = scene->getComponent<Range>(enemy);
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < range->range ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  });
  factory.registerSimpleCondition("AttackPlayer", [&, enemy](BT::TreeNode &) {
    auto enemyAttack = scene->getComponent<Attack>(enemy)->attack;
    auto playerHp = &scene->getComponent<Hp>(player)->hp;
    *playerHp -= enemyAttack;
    CombatLog::addLog((std::stringstream() << "-----" << scene->getComponent<Name>(enemy)->name << "-----").str(), LogType::COMBAT);
    CombatLog::addLog((std::stringstream() << "player was hit with " << enemyAttack << " damage").str(), LogType::COMBAT);
    CombatLog::addLog((std::stringstream() << "player has " << *playerHp << " hp left").str(), LogType::COMBAT);
    return BT::NodeStatus::SUCCESS;
  });
  factory.registerSimpleCondition("ApproachPlayer",
                                  [&, enemy](BT::TreeNode &) {
                                    auto playerPos = &scene->getComponent<Position>(player)->pos;
                                    auto enemyPos = &scene->getComponent<Position>(enemy)->pos;
                                    auto distance = sf::Vector2i(playerPos->x - enemyPos->x, playerPos->y - enemyPos->y);
                                    bool hor = abs(distance.x) > abs(distance.y);
                                    if (hor) {
                                      if (distance.x > 0) {
                                        *enemyPos += sf::Vector2i(1, 0);
                                      } else if (distance.x < 0) {
                                        *enemyPos += sf::Vector2i(-1, 0);
                                      }
                                    } else {
                                      if (distance.y > 0) {
                                        *enemyPos += sf::Vector2i(0, 1);
                                      } else if (distance.y < 0) {
                                        *enemyPos += sf::Vector2i(0, -1);
                                      }
                                    }

                                    return BT::NodeStatus::SUCCESS;
                                  }

  );
  if (variant == 0) {
    scene->addComponents(enemy, std::make_shared<BodyColor>(sf::Color::Red), std::make_shared<Position>(sf::Vector2i(2, 2)),
                         std::make_shared<Name>((std::string) "Fag"), std::make_shared<Size>(40, 40), std::make_shared<Sight>(14), std::make_shared<Range>(7),
                         std::make_shared<Attack>(7),
                         std::make_shared<BehaviorTree>(std::move(factory), fs::current_path().parent_path() / "resources" / "behavior_trees" / "my_tree.xml",
                                                        BtType::LONG_RANGE));
  } else if (variant == 1) {
    scene->addComponents(enemy, std::make_shared<BodyColor>(sf::Color::Green), std::make_shared<Position>(sf::Vector2i(10, 5)),
                         std::make_shared<Name>((std::string) "Goblin"), std::make_shared<Size>(40, 40), std::make_shared<Sight>(20),
                         std::make_shared<Range>(10), std::make_shared<Attack>(3),
                         std::make_shared<BehaviorTree>(std::move(factory), fs::current_path().parent_path() / "resources" / "behavior_trees" / "my_tree.xml",
                                                        BtType::LONG_RANGE));
  }
  return enemy;
}

void EnemySystem::setPlayer(EntityID player) {
  this->player = player;
}

void EnemySystem::enemyTurn() {
  for (const auto &enemy : enemies) {
    std::cout << "enemy turn" << std::endl;
    scene->getComponent<BehaviorTree>(enemy)->tree.tickOnce();
    std::cout << "enemy turn done" << std::endl;
  }
}