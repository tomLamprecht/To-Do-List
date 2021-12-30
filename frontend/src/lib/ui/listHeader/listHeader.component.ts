import { Component, Input } from '@angular/core';

@Component({
  selector: 'listHeader',
  templateUrl: './listHeader.component.html',
  styleUrls: ['./listHeader.component.scss'],
})
export class ListHeaderComponent {
  @Input()
  title = 'listHeader';

}
