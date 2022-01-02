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

   emitOnDisplay(event) {
     this.onDisplay.emit(event);
   }

}
