CREATE TABLE IF NOT EXISTS t_item_identifier (
  id INTEGER PRIMARY KEY,
  m_family TEXT,
  m_order TEXT,
  m_type TEXT,
  m_form TEXT,
  m_name TEXT
);

INSERT INTO t_item_identifier (m_family, m_order, m_type, m_form, m_name) VALUES ('Resource', 'Wood', 'Maple', 'Tree', 'Maple Tree');
INSERT INTO t_item_identifier (m_family, m_order, m_type, m_form, m_name) VALUES ('Resource', 'Wood', 'Maple', 'Log', 'Maple Log');