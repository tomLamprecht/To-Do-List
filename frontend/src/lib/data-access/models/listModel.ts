import { ReminderItemModel } from './reminderItemModel';

export interface ListModel {
  id: number;
  name: String;
  reminderItems: ReminderItemModel[];
}
