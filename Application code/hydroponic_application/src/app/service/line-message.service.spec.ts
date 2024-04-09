import { TestBed } from '@angular/core/testing';

import { LineMessageService } from './line-message.service';

describe('LineMessageService', () => {
  let service: LineMessageService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(LineMessageService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
