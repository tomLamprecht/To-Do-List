import { Component, EventEmitter, Input, Output, SimpleChange } from '@angular/core';
import { ReminderItemModel } from '../../data-access/models/reminderItemModel';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent {
  @Input()
  title = 'list';

  @Input()
  idList: number;

  @Input()
  reminderItems: ReminderItemModel[];

  @Output()
  changeTitleEvent = new EventEmitter<string>();

  @Output()
  updateRequest = new EventEmitter<string>();

  addEmptyReminderItem() {
    this.reminderItems.push({
      id: (Math.random() * 10000) | 0,
      title: 'empty',
      flag: false,
      position: 0,
      timestamp: '',
    });
  }

  deleteReminderItem(reminderItem:ReminderItemModel) {
    var index = this.reminderItems.indexOf(reminderItem);
    this.reminderItems.splice(index, 1);
    this.updateRequest.emit();
  }

  renameReminderItem(reminderItem, event) {
    reminderItem.title = event;
  }

  changeReminderDate(reminderItem, event) {
    reminderItem.timestamp = event;
    this.updateRequest.emit();
  }

  onChangeTitle(event) {
    this.changeTitleEvent.emit(event.target.value);
  }

  onToggleFlag(reminderItem:ReminderItemModel, flag:boolean) {
    reminderItem.flag = flag;
    this.updateRequest.emit();
  }

  plsUnfocus:boolean = false;

  ngOnChanges(changes :SimpleChange){
    if(changes["idList"] == undefined){
      this.plsUnfocus = false;
    }else{
      this.plsUnfocus = true;
    }

  }

  ngAfterViewChecked(){
    if(this.plsUnfocus){
    var tmp = document.createElement("input");
    document.body.appendChild(tmp);
    tmp.focus();
    document.body.removeChild(tmp);
    }
    this.plsUnfocus = false;
  }

}
