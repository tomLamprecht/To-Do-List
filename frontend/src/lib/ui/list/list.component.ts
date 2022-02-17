import { Component, EventEmitter, Input, Output, SimpleChange } from '@angular/core';
import { BackendService } from 'src/lib/feature/backend.service';
import { ReminderItemModel } from '../../data-access/models/reminderItemModel';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent {

  constructor(private backendService: BackendService){}

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

    this.backendService.postReminder(this.idList, "", "", "0").subscribe( (resp) => this.reminderItems.push(resp));
  }

  deleteReminderItem(reminderItem:ReminderItemModel) {
    var index = this.reminderItems.indexOf(reminderItem);
    this.reminderItems.splice(index, 1);
    this.backendService.deleteReminder(reminderItem.id).subscribe(resp => {this.updateRequest.emit();});
  }


  updateReminderItem(reminderItem){
    this.backendService.putReminder(reminderItem.id, reminderItem.title, reminderItem.timestamp, reminderItem.flag).subscribe( (resp) => {this.updateRequest.emit();});
  }

  renameReminderItem(reminderItem, event) {
    reminderItem.title = event;
    this.updateReminderItem(reminderItem);
  }

  changeReminderDate(reminderItem, event) {
    reminderItem.timestamp = event;
    this.updateReminderItem(reminderItem);
  }

  onChangeTitle(event) {
    this.changeTitleEvent.emit(event.target.value);
  }

  onToggleFlag(reminderItem:ReminderItemModel, flag:boolean) {
    reminderItem.flag = flag;
    this.updateReminderItem(reminderItem);
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
