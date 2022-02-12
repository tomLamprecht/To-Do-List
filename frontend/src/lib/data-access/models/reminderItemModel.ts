export interface ReminderItemModel {
  id: number;
  title: string;
  timestamp: string;
  flag: boolean;
}

// string sqlCreateTableReminder =
//     "create table if not exists reminder("
//     "id integer not null primary key autoincrement,"
//     "title text not null,"
//     "timestamp text not null,"
//     "position integer not null,"
//     "list_id integer not null,"
//     "flag integer not null,"
//     "unique (position, list_id),"
//     "foreign key (list_id) references list (id));";

//  {
//     "id": 0,
//     "title": "string",
//     "position": 0,
//     "timestamp": "2021-12-09"
//   }
