import { Component, EventEmitter, Input, Output } from '@angular/core';
import { ListModel } from 'src/lib/data-access/models/listModel';

@Component({
  selector: 'listHeaderContainer',
  templateUrl: './listHeaderContainer.component.html',
  styleUrls: ['./listHeaderContainer.component.scss'],
})
export class ListHeaderContainerComponent {
  @Input()
  title = 'listHeaderContainer';

  @Input()
  lists: ListModel[];

  @Output()
  onDisplay = new EventEmitter<ListModel>();

  @Output()
  deleteListEvent = new EventEmitter<ListModel>();


   emitOnDisplay(event) {
     this.onDisplay.emit(event);
   }

   addEmptyList() {
    this.lists.push({
      id: (Math.random() * 10000) | 0,
      name: 'new List',
      position: 0,
      reminderItems: [],
    });
  }

  changeListTitle(list ,event){
    list.name = event;
  }

  onDeleteList(list){
    this.deleteListEvent.emit(list);

  }

  // deleteColumn(column:ColumnModel) {
  //   var index = this.columns.indexOf(column);
  //   this.columns.splice(index, 1);
  // }

  // changeColumnTitle(column, event) {
  //   column.name = event;
  // }

  // ngAfterViewInit() {
  //   var tmp = document.createElement("input");
  //   document.body.appendChild(tmp);
  //   tmp.focus();
  //   document.body.removeChild(tmp);
  // }

}
