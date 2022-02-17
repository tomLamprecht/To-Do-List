import { Component, ElementRef, EventEmitter, Input, Output, ViewChild } from '@angular/core';

@Component({
  selector: 'reminderItem',
  templateUrl: './reminderItem.component.html',
  styleUrls: ['./reminderItem.component.scss'],
})
export class ReminderItemComponent {
  @Input()
  title = 'reminderItem';

  @Input()
  idReminderItem = 'reminderItem';

  @Input()
  date:string;

  @Input()
  flagged:boolean;

  @Output()
  deleteReminderItemEvent = new EventEmitter();

  @Output()
  nameChangeEvent = new EventEmitter<string>();

  @Output()
  dateChangeEvent = new EventEmitter<string>();

  @Output()
  toggleFlagEvent = new EventEmitter<boolean>();

  @ViewChild('inputName') input : ElementRef

  checkboxMarked:boolean = false;



  timerDeleteReminderItem() {
    this.checkboxMarked=true;
    setTimeout(()=>{this.deleteReminderItem()}, 3000);
  }

  deleteReminderItem() {
    if(this.checkboxMarked) {
      let element = document.getElementById("reminderItem" + this.idReminderItem);
      element.className = "cardDelete";
      let animations = element.getAnimations();
      let temp = this.deleteReminderItemEvent;
      for( let animation of animations){
        if (animation["animationName"] == "delete"){
          animation["finished"].then( function(value) { temp.emit(); } , function(reason){console.log(reason);});
        }
      }
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

  ngAfterViewInit(){
    this.input.nativeElement.focus();
  }
}
