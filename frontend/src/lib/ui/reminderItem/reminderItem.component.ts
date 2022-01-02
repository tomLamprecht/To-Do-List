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

  @Output()
  deleteReminderItemEvent = new EventEmitter();

  checkboxMarked:boolean = false;

  timerDeleteReminderItem() {
    this.checkboxMarked=true;
    setTimeout(()=>{this.deleteReminderItem()}, 3000);
  }

  deleteReminderItem() {
    if(this.checkboxMarked) {
      this.deleteReminderItemEvent.emit();
    }
  }

}
