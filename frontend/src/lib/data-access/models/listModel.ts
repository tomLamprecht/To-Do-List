import { ReminderItemModel } from './reminderItemModel';

export interface ListModel {
  id: number;
  name: String;
  reminderItems: ReminderItemModel[];
}

// string sqlCreateTableList =
//         "create table if not exists list("
//         "id integer not null primary key autoincrement,"
//         "name text not null,"
//         "position integer not null UNIQUE);";


// {
//   "id": 0,
//   "name": "string",
//   "position": 0,
//   "items": [
//     {
//       "id": 0,
//       "title": "string",
//       "position": 0,
//       "timestamp": "2021-12-09T10:04:42.058Z"
//     }
//   ]
// }
