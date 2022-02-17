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

  @Output()
  newListEvent = new EventEmitter<ListModel>();

  @Output()
  changeTitleEvent = new EventEmitter<[ListModel, string]>();


   emitOnDisplay(event) {
     this.onDisplay.emit(event);
   }

   requestNewList(){
     this.newListEvent.emit();
   }


  changeListTitle(list ,event){
    this.changeTitleEvent.emit([list,event]);
  }

  onDeleteList(list){
    this.deleteListEvent.emit(list);

  }

}
