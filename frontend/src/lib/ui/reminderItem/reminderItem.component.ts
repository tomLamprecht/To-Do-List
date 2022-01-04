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

  @Input()
  date:string;

  @Output()
  deleteReminderItemEvent = new EventEmitter();

  @Output()
  nameChangeEvent = new EventEmitter<string>();

  @Output()
  dateChangeEvent = new EventEmitter<string>();

  @Output()
  toggleFlagEvent = new EventEmitter<boolean>();

  checkboxMarked:boolean = false;
  flagged:boolean = false;

  timerDeleteReminderItem() {
    this.checkboxMarked=true;
    setTimeout(()=>{this.deleteReminderItem()}, 3000);
  }

  deleteReminderItem() {
    if(this.checkboxMarked) {
      this.deleteReminderItemEvent.emit();
    }
  }

  onChangeName(event) {
    this.nameChangeEvent.emit(event.target.value);
  }

  onChangeDate(event) {
    this.dateChangeEvent.emit(event.target.value);
  }

  toggleFlag() {
    this.flagged = !this.flagged;
    this.toggleFlagEvent.emit(this.flagged);
  }

}
