import { Component, ElementRef, EventEmitter, Input, Output, ViewChild } from '@angular/core';
import { ListModel } from 'src/lib/data-access/models/listModel';

@Component({
  selector: 'listHeader',
  templateUrl: './listHeader.component.html',
  styleUrls: ['./listHeader.component.scss'],
})
export class ListHeaderComponent {
  @Input()
  title = 'listHeader';

   @Input()
   list: ListModel;

   @Output()
   onDisplay = new EventEmitter<ListModel>();

  @Output()
  onTitleChangeEvent = new EventEmitter<string>();

  @Output()
  onDeleteEvent = new EventEmitter();

  @ViewChild('inputHeader') input : ElementRef

  @ViewChild('header') header : ElementRef

   emitOnDisplay() {
     this.onDisplay.emit(this.list);
   }

   onEditClick(event){
     event.stopPropagation();
     this.input.nativeElement.disabled = false;
     this.input.nativeElement.focus();
   }

   onTitleChange(event){
    this.onTitleChangeEvent.emit(event.target.value);
  }

    ngAfterViewInit(){
      this.input.nativeElement.disabled = false;
      this.input.nativeElement.focus();
    }

    onDelete(event){
      event.stopPropagation();
      this.header.nativeElement.className = "listHeaderDelete";
      let temp = this.onDeleteEvent;
      let animations = document.getElementById('listheader' + this.list.id).getAnimations();
      for( let animation of animations){
        if (animation["animationName"] == "fallAway"){
          animation["finished"].then( function(value) { temp.emit(); } , function(reason){console.log(reason);});
        }
      }

    }

}
