import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'reminderItem',
  templateUrl: './reminderItem.component.html',
  styleUrls: ['./reminderItem.component.scss'],
})
export class ReminderItemComponent {
  @Input()
  title = 'reminderItem'; // title: string = "item";

  @Input()
  idReminderItem = 'reminderItem';

}
