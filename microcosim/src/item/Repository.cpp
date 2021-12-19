#include "src/item/Repository.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/game/State.hpp"
#include "src/database/Context.hpp"
#include <memory>

namespace Item {

  Repository::Repository(std::shared_ptr<game::State> gameState) {
    GameState = gameState;
  }
 
  std::shared_ptr<std::vector<std::shared_ptr<Item::ItemIdentifier>>> Repository::SelectAllIdentifier() {
    std::string sql = "SELECT m_family, m_order, m_type, m_form, m_name FROM t_item_identifier"; 
    sqlite3* db;
    sqlite3_stmt* stmt;
    GameState->DbContext->PrepareDbAndStmt(&db, &stmt, sql);
    std::vector<std::shared_ptr<Item::ItemIdentifier>> identifiers;
    int rc = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      Item::ItemIdentifier identifier;
      identifier.Family = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
      identifier.Order = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
      identifier.Type = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
      identifier.Form = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
      identifier.Name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
      identifiers.push_back(std::make_shared<Item::ItemIdentifier>(identifier));
    }
    GameState->DbContext->FinishSqlConn(&db, &stmt);
    auto res = std::make_shared<std::vector<std::shared_ptr<Item::ItemIdentifier>>>(identifiers);
    return res;
  }

  std::shared_ptr<std::vector<std::shared_ptr<Item::ItemIdentifier>>> Repository::SelectFamilies() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT DISTINCT m_family FROM t_item_identifier";
    GameState->DbContext->PrepareDbAndStmt(&db, &stmt, sql);
    std::vector<std::shared_ptr<Item::ItemIdentifier>> identifiers;
    int rc = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      Item::ItemIdentifier identifier;
      identifier.Family = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
      identifiers.push_back(std::make_shared<Item::ItemIdentifier>(identifier));
    }
    GameState->DbContext->FinishSqlConn(&db, &stmt);
    auto res = std::make_shared<std::vector<std::shared_ptr<Item::ItemIdentifier>>>(identifiers);
    return res;
  }

  std::shared_ptr<std::vector<std::shared_ptr<Item::ItemIdentifier>>> Repository::SelectOrders(Item::ItemIdentifier identifier) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT DISTINCT m_order FROM t_item_identifier WHERE m_family = ?";
    GameState->DbContext->PrepareDbAndStmt(&db, &stmt, sql);
    sqlite3_bind_text(stmt, 1, identifier.Family.c_str(), identifier.Family.length(), NULL);
    std::vector<std::shared_ptr<Item::ItemIdentifier>> identifiers;
    int rc = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      Item::ItemIdentifier identifier;
      identifier.Order = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
      identifiers.push_back(std::make_shared<Item::ItemIdentifier>(identifier));
    }
    GameState->DbContext->FinishSqlConn(&db, &stmt);
    auto res = std::make_shared<std::vector<std::shared_ptr<Item::ItemIdentifier>>>(identifiers);
    return res;
  }

  std::shared_ptr<std::vector<std::shared_ptr<Item::ItemIdentifier>>> Repository::SelectType(Item::ItemIdentifier identifier) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT DISTINCT m_type FROM t_item_identifier WHERE m_family = ? AND m_order = ?";
    GameState->DbContext->PrepareDbAndStmt(&db, &stmt, sql);
    sqlite3_bind_text(stmt, 1, identifier.Family.c_str(), identifier.Family.length(), NULL);
    sqlite3_bind_text(stmt, 2, identifier.Order.c_str(), identifier.Order.length(), NULL);
    std::vector<std::shared_ptr<Item::ItemIdentifier>> identifiers;
    int rc = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      Item::ItemIdentifier identifier;
      identifier.Type = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
      identifiers.push_back(std::make_shared<Item::ItemIdentifier>(identifier));
    }
    GameState->DbContext->FinishSqlConn(&db, &stmt);
    auto res = std::make_shared<std::vector<std::shared_ptr<Item::ItemIdentifier>>>(identifiers);
    return res;
  }

  std::shared_ptr<std::vector<std::shared_ptr<Item::ItemIdentifier>>> Repository::SelectForm(Item::ItemIdentifier identifier) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT DISTINCT m_form FROM t_item_identifier WHERE m_family = ? AND m_order = ? AND m_type = ?";
    GameState->DbContext->PrepareDbAndStmt(&db, &stmt, sql);
    sqlite3_bind_text(stmt, 1, identifier.Family.c_str(), identifier.Family.length(), NULL);
    sqlite3_bind_text(stmt, 2, identifier.Order.c_str(), identifier.Order.length(), NULL);
    sqlite3_bind_text(stmt, 3, identifier.Type.c_str(), identifier.Order.length(), NULL);
    std::vector<std::shared_ptr<Item::ItemIdentifier>> identifiers;
    int rc = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      Item::ItemIdentifier identifier;
      identifier.Form = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
      identifiers.push_back(std::make_shared<Item::ItemIdentifier>(identifier));
    }
    GameState->DbContext->FinishSqlConn(&db, &stmt);
    auto res = std::make_shared<std::vector<std::shared_ptr<Item::ItemIdentifier>>>(identifiers);
    return res;
  }

}